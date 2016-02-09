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
int main()
{
	printf("SERVER PROGRAM	\n");
	int n;
	printf("enter no of clients");
	scanf("%d",&n);
	int i;
	char name[100];
	char fifos[n][100];
	int fd[n];
	struct pollfd pfds[n];
	for(i=0;i<n;i++)
	{
		strcpy(name,"client");
		char a[10];
		a[0]=(i+1)+'0';
		a[1]='\0';
		strcat(name,a);
		mkfifo(name,0666);
		fd[i]=open(name,O_RDWR);
		pfds[i].fd=fd[i];
		pfds[i].events=POLLIN;
	}
	while(1)
	{
	int ret=poll(pfds,n,1000);
	if(ret)
	{
	//	printf("ready\n");
		int i;
		for(i=0;i<n;i++)
		{
			if(pfds[i].revents!=0)
			{
			char msg[100];
			int len=read(fd[i],msg,100);
		//	printf(" %s \n",msg);
			int  j;
			for(j=0;j<n;j++)
			{
				if(i!=j)
				{
					printf(" %s \n",msg);
					write(fd[j],msg,len);
				}
			}
			}
		}
		sleep(7);
	}
	}
}
