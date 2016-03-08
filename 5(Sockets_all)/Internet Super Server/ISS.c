#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
int main()
{
	//2 services at present
	int ns=2;
	int sfd[ns],nsfd[ns];
	int pp[ns][2];
	int samp;
	mkfifo("f",0666|IPC_CREAT);
	samp=open("f",O_RDWR);
	int ffd[ns*3];		//3 clients max for each server
	struct sockaddr_in my_addrs[2],client_addrs;
	int port[ns];
	int client_addrslen;
	port[0]=6000;
	port[1]=6020;

	int i=0;

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
	if(maxfd<sfd[i])
		maxfd=sfd[i];
	}

	
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
					nsfd[i]=accept(sfd[i],(struct sockaddr *)&client_addrs,&client_addrslen);
					int cc=fork();
					pipe(pp[i]);
					if(cc==0)		//child
					{
			//			printf("child\n");
					 	close(sfd[i]);
					 	close(pp[i][0]);
					 	dup2(nsfd[i],0);
					 	dup2(samp,1);				//extend the program to many fifos or either a separate socekt in ISS which each server reqs for output
					// 	dup2(nsfd[i],1);
					 //	dup2(pp[i][1],1);
					 	if(i==0)
					 	execv("service1",NULL);
					 	else
					 		execv("service2",NULL);
					// 	char buffer[100],buf[100];
					// strcpy(buffer,"");
					// int d=recv(nsfd[i],buffer,100,0);
					// if(d>0)
					// printf("server read");
					// write(1,buffer,d);
					// printf("\n");
					// strcpy(buffer,"");
					// printf("enter reply\n");
					// scanf("%s",buf);
					// send(nsfd[i],buf,strlen(buf),0);
			//		exit(0);
					}
					else
					{
				//		printf("parent\n");
					//	wait(NULL);
						close(nsfd[i]);
						close(pp[i][1]);
						char buf[100];
					//	wait(NULL);
					//	printf("in parent again\n");
						int r=read(samp,buf,100);
						write(1,buf,r);
						printf("\n");
					//	printf("%s\n",buf);
					//	while(read(pp[i][0],buf,100)<=0) { //printf("not avail");} 
					//	if(d>0)
					//	printf("%s\n", buf);
					}
		
					}
				}
			}
			
		}
}