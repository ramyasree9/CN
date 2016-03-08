#include <stdio.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
int *freed_pf;
int *pid;		//pids of platforms
int status[3];			//status of platforms
void handler()
{
	signal(SIGUSR2,handler);
	status[*freed_pf-1]=0;
	printf("platform freed\n");
}
int main()
{
	signal(SIGUSR2,handler);
	int shmid=shmget(1234,4*sizeof(int),0666|IPC_CREAT);
	pid=(int *)shmat(shmid,NULL,0);
	pid[0]=getpid();
	int port_pf[3];			//addrs of platforms
	port_pf[0]=6050;
	port_pf[1]=6060;
	port_pf[2]=6070;

	int shmid1=shmget(1235,sizeof(int),0666|IPC_CREAT);
	freed_pf=(int *)shmat(shmid1,NULL,0);

	int sfd[3],nsfd[10],c=0;
	struct sockaddr_in client_addrs[10];
	int client_addrs_len[10];
	int port[3];
	port[0]=6020;
	port[1]=6030;
	port[2]=6040;
	struct sockaddr_in my_addrs[3];
	int i=0;
	int maxfd=0;
	for(i=0;i<3;i++)
	{
		status[i]=0;
	my_addrs[i].sin_family=AF_INET;
	my_addrs[i].sin_addr.s_addr=INADDR_ANY;
	my_addrs[i].sin_port=htons(port[i]);
	sfd[i]=socket(AF_INET,SOCK_STREAM,0);
	bind(sfd[i],(struct sockaddr *)&my_addrs[i],sizeof(struct sockaddr_in));
	listen(sfd[i],10);
	if(maxfd<sfd[i])
		maxfd=sfd[i];
	}

	fd_set rfds;
	int ret;
	struct timeval tv;
	int free_pf=-1;

	while(1)
	{
		for(i=0;i<3;i++)
		{
			if(status[i]==0)
			{
				free_pf=i;
				break;
			}
		}
		if(free_pf!=-1)
		{
		tv.tv_sec=0;
		tv.tv_usec=10;
		FD_ZERO(&rfds);
		FD_SET(sfd[0],&rfds);
		FD_SET(sfd[1],&rfds);
		FD_SET(sfd[2],&rfds);
		ret=select(maxfd+1,&rfds,NULL,NULL,&tv);
		if(ret>0)
		{
			for(i=0;i<3;i++)
			{
				if(FD_ISSET(sfd[i],&rfds))
				{
					int j;
					client_addrs_len[c]=sizeof(struct sockaddr_in);
					nsfd[c]=accept(sfd[i],(struct sockaddr *)&client_addrs[c],&client_addrs_len[c]);
					printf("sm accepted\n");
					for(j=1;j<=3;j++)
					{
						kill(pid[j],SIGUSR2);
					}
					kill(pid[free_pf+1],SIGUSR1);
					status[free_pf]=1;
					char buffer[100];
					sprintf(buffer,"%d",port_pf[free_pf]);
					send(nsfd[c],buffer,strlen(buffer),0);
					c++;
				}
			}
		}
		}
		
	}

}