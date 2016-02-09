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
	char name1[100];
	int rfd[n],wfd[n];
	char a[10];
	struct pollfd pfds[n];
	char rfifo[n][100],wfifo[n][100];
	for(i=0;i<n;i++)
	{
	//	printf("s %d\n",i);
		strcpy(name,"client");
		sprintf(a,"%d",(i+1));
		//a[0]=(i+1)+'0';
		//a[1]='\0';
		strcat(name,a);
		strcpy(name1,name);
		strcat(name1,"w");
		strcat(name,"r");
	//	printf("%s\n",name);
	//	printf("%s\n",name1);
		strcpy(rfifo[i],name1);
		strcpy(wfifo[i],name);
		mkfifo(name,0666);
		mkfifo(name1,0666);
		// rfd[i]=open(name1,O_RDONLY);		//open write fifo in read mode to poll
		// wfd[i]=open(name,O_WRONLY);		//open read fifo in write mode	to write into them
		// pfds[i].fd=rfd[i];
		// pfds[i].events=POLLIN;
	//	printf("complete\n");
	}
	for(i=0;i<n;i++)
	{
	//	printf("s \n");
		rfd[i]=open(rfifo[i],O_RDWR);		//open write fifo in read mode to poll
		// wfd[i]=open(wfifo[i],O_WRONLY);		//open read fifo in write mode	to write into them
		pfds[i].fd=rfd[i];
		pfds[i].events=POLLIN;
	//	printf("complete\n");
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
			int len=read(rfd[i],msg,100);
			printf(" %s \n",msg);
			int  j;
			for(j=0;j<n;j++)
			{
				if(i!=j)
				{
				//	printf(" %s \n",msg);
					wfd[j]=open(wfifo[j],O_RDWR);	//won;y
					write(wfd[j],msg,len);
				}
			}
			}
		}
		sleep(2);
	}
	}
}
