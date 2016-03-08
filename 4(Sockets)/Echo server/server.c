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
				close(sfd);
				while(1)
				{
					char buffer[100],buf[100];
			strcpy(buffer,"");
			int d=recv(nsfd,buffer,100,0);
			if(d>0)
	//		printf("server read");
			write(1,buffer,d);
			printf("\n");
			strcpy(buffer,"");
		//	printf("enter reply\n");
			scanf("%s",buf);
			send(nsfd,buf,strlen(buf),0);
			sleep(3);
				}
				
			exit(0);
			}
			else
			{
				close(nsfd);
			}
		
		}
}