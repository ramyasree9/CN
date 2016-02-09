#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
int main()
{
	
//	printf("SERVICE PROGRAM 1\n");		//wont appear since popened with r
	mkfifo("fifo1",0666);
	int fd=open("fifo1",O_RDWR);

		fd_set rfds;
		FD_ZERO(&rfds);
		FD_SET(fd,&rfds);
		char msg[100];
		struct timeval tv;
		int max=fd+1;
	while(1)
	{
		tv.tv_sec=1;
		tv.tv_usec=0;
		FD_ZERO(&rfds);
		FD_SET(fd,&rfds);
	    int ret=select(max,&rfds,NULL,NULL,&tv);
	    if(ret==-1)
	    	perror("select error\n");
	    else if(ret)
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
