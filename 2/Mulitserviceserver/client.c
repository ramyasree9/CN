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
	while(1)
	{
		int n;
		printf("enter the service no- client %s wants\n",argv[1]);
		scanf("%d",&n);
		char s[10];
		sprintf(s,"%d",n);
		strcat(s,"|");
		strcat(s,filename);
		strcat(s,"|");
//		printf("client is writing %s to mss fifo",s);
		int fd1=open("Mssf",O_RDWR);
		write(fd1,s,strlen(s));		//not checked for synchronisation
		 sleep(2);
		 char buffer[100];
		 read(fd,buffer,100);
		 int i=0;
		 while(buffer[i]!='|')
		 	i++;
		 buffer[i]='\0';
		 printf("%s\n",buffer);
		// if(n==1)		//service of reading a file
		// {
		// 	printf("enter file name to read by service 1\n");
		// 	char file[100];
		// 	scanf("%s",file);
		// 	write(fd,file,strlen(file));
		// 	sleep(5);
		// 

		// 	read(fd,buffer,1000);
		// 	printf("service 1 read %s\n",buffer);
		//}
	}
}
