#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <poll.h>
int main(int argc,char *argv[])
{
	
	while(1)
	{
		printf("enter the service no client %s needs \n",argv[1]);
		int n;
		scanf("%d",&n);
		int fd=open("Logfifo",O_RDWR);
		char buf[100];
		sprintf(buf,"%d",n);
		write(fd,buf,strlen(buf));
		sleep(2);
		strcpy(buf,"");
		read(fd,buf,100);
		int i=0;
		while(buf[i]!='|')
			i++;
		buf[i]='\0';
		printf("s msg received %s\n", buf);
		int fd1=open(buf,O_RDWR);
		strcpy(buf,"");
		sprintf(buf,"client %s is serviced by service %d|",argv[1],n);
		write(fd1,buf,strlen(buf));
	//	sleep(2);

	}
}
