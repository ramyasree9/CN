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
	char filename[100];
	strcpy(filename,"client");
	strcat(filename,argv[1]);
	strcat(filename,"fifo");
	printf("client 1 is creating fifo %s \n",filename);
	mkfifo(filename,0666);
	int fd=open(filename,O_RDWR);
	int fd1=open("Scfifo",O_RDWR);		//wronly
	while(1)
	{
		char c;
		printf("enter y if client %s wants service\n",argv[1]);
		scanf(" %c",&c);
		if(c=='y')
		{
			char name[100];
			strcpy(name,filename);
			strcat(name,"|");
			printf("client is writing its fifo name as %s\n",name);
			write(fd1,name,strlen(name));
			sleep(4);		//wait before sc coordinates service 
			char msg[100];
			read(fd,msg,100);
			printf("client  received :%s\n",msg);
		}
			// printf("enter file name to read by service 1\n");
			// char file[100];
			// scanf("%s",file);
			// write(fd,file,strlen(file));
			// sleep(5);
			// char buffer[1000];	
			// read(fd,buffer,1000);
			// printf("service 1 read %s\n",buffer);
	}
}
