
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <poll.h>
int main()
{
	
//	printf("SERVICE PROGRAM 1\n");		//wont appear since popened with r
	mkfifo("fifo2",0666);
	int fd=open("fifo2",O_RDWR);

		struct pollfd pfds[1];
	    pfds[0].fd=fd;
	    pfds[0].events=POLLIN;
	//    printf("in service");
	 //   write(1,"vdnkj",10);
		char msg[100];
	//	strcpy(msg,"serv entered");
	//	write(fd,msg,strlen(msg));
	while(1)
	{
	//	printf("in service1");
	//	sleep(5);
	    int ret=poll(pfds,1,1000);
	    if(ret)
	    {
		read(fd,msg,100);
		int i=0;
		while(msg[i]!='|')
			i++;
		msg[i]='\0';
		write(1,msg,strlen(msg));
	//	printf("%s",msg);
	//	strcpy(msg,"mesg received");
	//	write(fd,msg,strlen(msg));
	//	sleep(5);
		// if((msg[0]>=65 && msg[0]<=90) || (msg[0]>=97 && msg[0]<=122) || (msg[0]>=48 && msg[0]<=57))
		// {
		// 	printf("service 1 received -%s",msg);
		// }
	    }
	    //else
	   // 	printf("no input \n");
	}
}
