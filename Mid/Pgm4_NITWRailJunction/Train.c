#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("enter correct no of arguments (cmd line)\n");
		exit(0);
	}
	char comp[100];
	sprintf(comp,"train %s compartments",argv[1]);
	struct sockaddr_in Sm_addrs;
	Sm_addrs.sin_family=AF_INET;
	int port=6020;
	Sm_addrs.sin_addr.s_addr=INADDR_ANY;
	Sm_addrs.sin_port=htons(port);
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	connect(sfd,(struct sockaddr *)&Sm_addrs,sizeof(struct sockaddr_in));


//	while(1)
	{
		char buffer[100];
		recv(sfd,buffer,100,0);
		int port1=atoi(buffer);
		printf("train got %d\n",port1 );
		struct sockaddr_in pf_addrs;
		pf_addrs.sin_port=htons(port1);
		pf_addrs.sin_family=AF_INET;
		pf_addrs.sin_addr.s_addr=INADDR_ANY;
		int sfd1=socket(AF_INET,SOCK_STREAM,0);
		int ret=connect(sfd1,(struct sockaddr *)&pf_addrs,sizeof(struct sockaddr_in));
	//	Sm_addrs.sin_port=htons(port1);
	//	int ret=connect(sfd,(struct sockaddr *)&Sm_addrs,sizeof(struct sockaddr_in));
		if(ret<0)
		perror("failed");
		else
			printf("success\n");
	//	char buffer[100];
		strcpy(buffer,"train");
		strcat(buffer,argv[1]);
		int r=send(sfd1,buffer,strlen(buffer),0);
		printf("%d\n",r );
		// printf("sending %s\n",comp );
		// send(sfd,comp,strlen(comp),0);
	}

}