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
int rfd,wfd;
void *fun1()					//keyboard to wfifo
{
	while(1)
	{
		char msg[100];
		scanf("%s",msg);
		write(wfd,msg,100);
	//	printf("wrote \n");
	//	sleep(7);
	}
}
void *fun2()					//readfifo to console
{
	while(1)
	{
	//	sleep(7);
		char msg[100];
		
		int c=read(rfd,msg,100);
		if((msg[0]>=65 && msg[0]<=90) || (msg[0]>=97 && msg[0]<=122) || (msg[0]>=48 && msg[0]<=57))
		printf(" %s\n",msg);
	}
}
int main(int argc,char *argv[])
{
	char readfifo[100],writefifo[100];
	strcpy(readfifo,"client");
	strcat(readfifo,argv[1]);
	char name[100];
	strcpy(writefifo,readfifo);
	strcat(readfifo,"r");
	strcat(writefifo,"w");
//	printf("%s %s \n",readfifo,writefifo);
	rfd=open(readfifo,O_RDWR);	//rdonly
	wfd=open(writefifo,O_RDWR);	//wronly
	int thrdid[2];
	pthread_t pid[2];
	pthread_create(&pid[0],NULL,fun1,NULL);
	pthread_create(&pid[1],NULL,fun2,NULL);
	// while(1)
	// {

	// }
	pthread_exit(NULL);	
}
