#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
int main()
{
	int sfd,nsfd;
	struct sockaddr_in my_addrs,client_addrs;
	int port=2020,client_addrslen;

	sfd=socket(AF_INET,SOCK_STREAM,0);

	memset(&my_addrs,0,sizeof(struct sockaddr_in));
	//bzero((char *)&my_addrs,sizeof(my_addrs));
	my_addrs.sin_family = AF_INET;
	my_addrs.sin_addr.s_addr = INADDR_ANY;
	my_addrs.sin_port=htons(port);

	bind(sfd,(struct sockaddr *)&my_addrs,sizeof(struct sockaddr_in));

	listen(sfd,3);
	while(1)
		{
			client_addrslen=sizeof(struct sockaddr_in);
			nsfd=accept(sfd,(struct sockaddr *)&client_addrs,&client_addrslen);
			int cc=fork();
			if(cc==0)		//child
			{
				printf("child\n");
				close(sfd);
				char in[10];
				int d=recv(nsfd,in,10,0);
				int sno=atoi(in);
				if(sno==1)
				{
				dup2(nsfd,0);
				dup2(nsfd,1);
				execv("server1",NULL);
				}
				else if(sno==2)
				{
				dup2(nsfd,0);
				dup2(nsfd,1);
				execv("server2",NULL);
				}
			}
			else
			{
				close(nsfd);
			}
		
		}
}