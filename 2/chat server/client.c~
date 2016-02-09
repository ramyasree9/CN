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
int fd;
char filename[100];
void *fun1()
{
	while(1)
	{
		char msg[100];
		scanf(" %s",msg);
		write(fd,msg,100);
		sleep(7);
	}
}
void *fun2()
{
	while(1)
	{
		sleep(7);
		char msg[100];
		
		int c=read(fd,msg,100);
		if((msg[0]>=65 && msg[0]<=90) || (msg[0]>=97 && msg[0]<=122) || (msg[0]>=48 && msg[0]<=57))
		printf(" %s\n",msg);
	}
}
int main(int argc,char *argv[])
{
	strcpy(filename,"client");
	strcat(filename,argv[1]);
	//printf("%s",filename);
	fd=open(filename,O_RDWR);
	int thrdid[2];
	pthread_t pid[2];
	pthread_create(&pid[0],NULL,fun1,NULL);
	pthread_create(&pid[1],NULL,fun2,NULL);
	while(1)
	{

	}
	pthread_exit(NULL);	
}
