#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#define ns 2
int main(int argc,char *argv[])
{
	//2 services at present
	int sfd[ns],nsfd[100];
	int cno=0;
	int flag[ns];
	int child_pid[ns];
	int i=0;
	for(i=0;i<ns;i++)
		flag[i]=0;
	struct sockaddr_in my_addrs[ns],client_addrs;
	int port[ns];
	int client_addrslen;
	port[0]=6000;
	port[1]=6020;

	//int i=0;

	int maxfd=0;
	fd_set rfds;
	struct timeval tv;
	tv.tv_usec=0;
	tv.tv_sec=2;
	FD_ZERO(&rfds);

	for(i=0;i<ns;i++)
	{	
	sfd[i]=socket(AF_INET,SOCK_STREAM,0);
	memset(&my_addrs[i],0,sizeof(struct sockaddr_in));
	my_addrs[i].sin_family = AF_INET;
	my_addrs[i].sin_addr.s_addr = INADDR_ANY;
	my_addrs[i].sin_port=htons(port[i]);
	bind(sfd[i],(struct sockaddr *)&my_addrs[i],sizeof(struct sockaddr_in));
	listen(sfd[i],3);
	FD_SET(sfd[i],&rfds);
	flag[i]=0;
	if(maxfd<sfd[i])
		maxfd=sfd[i];
	}

//	printf("no %d\n", argc);
//	printf("%s\n", argv[0]);

	int shmid=shmget(1234,sizeof(int),0666|IPC_CREAT);
	int *sent_sfd=(int *)shmat(shmid,NULL,0);
	//bzero((char *)&my_addrs,sizeof(my_addrs));
	

	while(1)
		{
			tv.tv_sec=2;
			FD_ZERO(&rfds);
			tv.tv_usec=3;
			for(i=0;i<ns;i++)
			FD_SET(sfd[i],&rfds);
			int ret=select(maxfd+1,&rfds,NULL,NULL,&tv);
			if(ret>0)
			{
				for(i=0;i<ns;i++)
				{
					if(FD_ISSET(sfd[i],&rfds))
					{
			//			printf("s avail %d\n",i );
						client_addrslen=sizeof(struct sockaddr_in);
						if(flag[i]==0)
						{

						nsfd[cno]=accept(sfd[i],(struct sockaddr *)&client_addrs,&client_addrslen);
				//		printf("got nsfd as %d\n",nsfd[cno]);
				//			printf("this is 1st time \n");
								flag[i]=1;
						int cc=fork();
						if(cc==0)		//child
						{
					//		printf("child\n");
						// 	close(sfd[i]);
						 	dup2(nsfd[cno],0);	
						// 	dup2(nsfd,1);	
						 	// if(i==0)
						 	// strcpy(argv[0],"service1");
						 	// else
						 	// strcpy(argv[0],"service2");
						//	sprintf(argv[1],"%d",sfd[i]);
						 //	argv[2]=NULL;
						 	*sent_sfd=sfd[i];

						 	if(i==0)
						 	{
						// 		printf("going to exec\n");
						 	execv("service1",NULL);

						 	}
						 	else
						 	{
						// 		printf("going to create serv2\n");
						 		execv("service2",NULL);
						 	}
						}
						else
						{
					//		printf("parent\n");
						//	wait(NULL);
						//	printf("parent\n");
							child_pid[i]=cc;
							//close(nsfd[cno]);
						}
						}
						else
						{
						//	printf("from second time\n");
							//do nothing
							// *pass_fd=nsfd[cno];
							// cno++;
							// printf("wrote tp shm %d\n",*pass_fd );
							// printf("signal sent\n");
							// kill(child_pid[i],SIGUSR1);
						}
				
		
					}
				}
			}
			
		}
}