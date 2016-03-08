#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include <netinet/in.h>
#include <stdlib.h>
int sfd;
void *write_msg()
{
		
	char buffer[100];
	while(1)
	{
	//	printf("enter smthng\n");
		strcpy(buffer,"");
		scanf("%s",buffer);
		int l=strlen(buffer);
		buffer[l]='|';
		buffer[l+1]='\0';
		send(sfd,buffer,strlen(buffer),0);	
	}
}
void *read_msg()
{
	struct pollfd pfd[1];
	pfd[0].fd=sfd;
	char buf[100];
	pfd[0].events=POLLIN;
	while(1)
	{
		int ret=poll(pfd,1,0);
		if(ret)
		{
			//sleep(2);
		//	printf("received\n");
			strcpy(buf,"");
			//while(recv(sfd,buf,100,0)<=0) {}
			int d=recv(sfd,buf,100,0);
			//	printf("received\n");
		//	printf("%s\n",buf);
			while(d<=0)
			{
				d=recv(sfd,buf,100,0);
			}
			//buf[d]='\0';
			int k=0;
			while(buf[k]!='\0' && buf[k]!='|')
				k++;
			buf[k]='\0';
			printf("%s\n",buf);
		//	write(1,buf,d);
		}
	}


}
int main(int argc, char const *argv[])
{
	int port;
	struct sockaddr_in server_addrs;

	sfd=socket(AF_INET,SOCK_STREAM,0);
	printf("enter prt 6000 or 6020\n");
	scanf("%d",&port);

	memset(&server_addrs,0,sizeof(struct sockaddr_in));
	server_addrs.sin_family= AF_INET;
	server_addrs.sin_port= htons(port);
	server_addrs.sin_addr.s_addr= INADDR_ANY;	//inet_addr("127.0.0.1");

	int ret=connect(sfd,(struct sockaddr *)&server_addrs,sizeof(struct sockaddr_in));
	pthread_t t1,t2;
	pthread_create(&t1,NULL,read_msg,NULL);
	pthread_create(&t2,NULL,write_msg,NULL);
	while(1)
	{

	}
	pthread_exit(NULL);
	return 0;
}