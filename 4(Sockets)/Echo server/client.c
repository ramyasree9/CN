#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	int sfd,port=2020;
	struct sockaddr_in server_addrs;

	sfd=socket(AF_INET,SOCK_STREAM,0);

	memset(&server_addrs,0,sizeof(struct sockaddr_in));
	server_addrs.sin_family= AF_INET;
	server_addrs.sin_port= htons(port);
	server_addrs.sin_addr.s_addr= INADDR_ANY;	//inet_addr("127.0.0.1");

	int ret=connect(sfd,(struct sockaddr *)&server_addrs,sizeof(struct sockaddr_in));
	if(ret<0)
		perror("connect");
	else
	{
		while(1)
		{
			char buffer[100],buf[100];
		//strcpy(buffer,"i am client ");
			//printf("en\n");
			scanf("%s",buffer);
		strcat(buffer,argv[1]);
		send(sfd,buffer,strlen(buffer),0);
		sleep(3);
		strcpy(buffer,"");
		int d=recv(sfd,buf,100,0);
		if(d>0)
			write(1,buf,d);
		printf("\n");
		}
		
	}

	return 0;
}