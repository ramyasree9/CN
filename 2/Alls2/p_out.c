#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <poll.h>
int main()
{
	/*		code below is for reading from a popen  remove while loop*/
//	while(1)
	{
		char msg[1000];
		printf("proc is reading msg for ALLS\n");
		printf("proc is reading msg for ALLS\n");
	//	scanf("%s",msg);
		read(0,msg,1000);
	//	mkfifo("dum",0666);
	//	int ffd=open("dum",O_RDWR);
	//	printf("out proc writing into fifo %s",msg);
	//	write(ffd,msg,strlen(msg));
		printf(" proc read %s \n",msg);
	//	if((msg[0]>=65 && msg[0]<=90) || (msg[0]>=97 && msg[0]<=122) || (msg[0]>=48 && msg[0]<=57))
		{
	//		printf("%s \n",msg);
		}
	 }

	/*   code below for reading from pipe of sig handle*/
	// char msg[1000];
	// printf("in out proc\n");
	// scanf("%s",msg);
	// printf("out proc read %s\n",msg);

	/*   code below for reading from a fifo  */
	// mkfifo("outfifo",0666);
	// 	int fd=open("outfifo",O_RDWR);

	// 	struct pollfd pfds[1];

	// 	pfds[0].events=POLLIN;
	// 	pfds[0].fd=fd;
	// while(1)
	// {
	// 	char buffer[1000];
	// 	int ret=poll(pfds,1,1000);
	// 	if(ret)
	// 	{

	// 	int r=read(fd,buffer,1000);
	// 	write(1,"out proc read\n",14);
	// 	write(1,buffer,r);
	// 	write(1,"\n",1);
	// 	}
	// 	else
	// 	{
	// 	//	printf("no data \n");
	// 	}
	// }
}
