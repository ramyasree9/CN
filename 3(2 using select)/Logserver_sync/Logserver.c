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
#include <sys/shm.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <ctype.h>
#define s 2
int ffd;
int fd[s+1];
struct timeval tv;
int max;
fd_set rfds;
char fifoname[s+1][100];
void *fun1()
{
	while(1)
	{
		char msg[100];
		read(ffd,msg,100);
		if((msg[0]>=65 && msg[0]<=90) || (msg[0]>=97 && msg[0]<=122) || (msg[0]>=48 && msg[0]<=57))
				//how to know if input is available or not by other than this method
		{
			printf("s msg received %s\n",msg);
			int no=atoi(msg);
			char name[100];
			strcpy(name,fifoname[no]);
			strcat(name,"|");
			write(ffd,name,strlen(name));
			sleep(4);
		}
	}
}
void *fun2()
{
	while(1)
	{
		tv.tv_usec=0;
		tv.tv_sec=1;
		FD_ZERO(&rfds);
		FD_SET(fd[1],&rfds);
		FD_SET(fd[2],&rfds);
		int ret=select(max,&rfds,NULL,NULL,&tv);
		if(ret==-1)
			perror("sel error\n");
		else if(ret)
		{
		//	printf("ready\n");
			int i;
		//	for(i=0;i<s;i++)
			{
				if(FD_ISSET(fd[1],&rfds))
				{
		//		printf(" %d is ready %d\n",i+1,pfds[i].revents);
				char buffer[100];
				read(fd[1],buffer,100);
				printf("service 1 : %s \n",buffer);
				}
				if(FD_ISSET(fd[2],&rfds))
				{
		//		printf(" %d is ready %d\n",i+1,pfds[i].revents);
				char buffer[100];
				read(fd[2],buffer,100);
				printf("service 2 : %s \n",buffer);
				}
			}
		}
		else
		{	
			//printf("no input\n");
		}
	}
}
int main()
{
	printf("LOG SERVER \n");
	int n;
	printf("enter no of clients \n");
	scanf("%d",&n);

	//int s=1;			//2 services
	strcpy(fifoname[1],"fifo1");
	strcpy(fifoname[2],"fifo2");

	
	FILE *fp=popen("./service1","r");
	fd[1]=fileno(fp);
	fp=popen("./service2","r");
	fd[2]=fileno(fp);

	
	// pfds[0].fd=fd[1];
	// pfds[1].fd=fd[2];
	// pfds[0].events=POLLIN;
	// pfds[1].events=POLLIN;
	FD_ZERO(&rfds);
	FD_SET(fd[1],&rfds);
	FD_SET(fd[2],&rfds);
	max=fd[1];
	if(max<fd[2])
		max=fd[2];
	max++;

	mkfifo("Logfifo",0666);
	ffd=open("Logfifo",O_RDWR);
	pthread_t pid[2];
	pthread_create(&pid[0],NULL,fun1,NULL);
	pthread_create(&pid[1],NULL,fun2,NULL);
	pthread_exit(NULL);	
	
}
