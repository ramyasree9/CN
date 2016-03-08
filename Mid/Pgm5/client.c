#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
int main()
{
	struct sockaddr_in server_addrs;
	int port=6020;
	memset(&server_addrs,0,sizeof(struct sockaddr_in));
	server_addrs.sin_family=AF_INET;
	server_addrs.sin_addr.s_addr=INADDR_ANY;
	server_addrs.sin_port=htons(port);
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	connect(sfd,(struct sockaddr *)&server_addrs,sizeof(struct sockaddr_in));
	char buffer[100];
	while(1)
	{
		recv(sfd,buffer,100,0);
		int i=0;
		while(buffer[i]!='\0' && buffer[i]!='|')
			i++;
		buffer[i]='\0';
		write(1,buffer,i);
		printf("\n");
	}
}