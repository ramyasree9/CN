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
#include <signal.h>
#include <ctype.h>
int *state;
int shm;
int *frees;
void sig_hand()					// for now -service 1 sends signal sigint after completion
								// service 2 sends signal 
{
	signal(SIGUSR2,sig_hand);
	state[*frees]=0;
}

int main()
{
	signal(SIGUSR2,sig_hand);
	printf("SERVCICE COORDINATOR PROGRAM  %d \n",getpid());
	int n;
	printf("enter no of clients");
	scanf("%d",&n);
	int s;
	printf("enter no of services");
	scanf("%d",&s);
	mkfifo("Scfifo",0666);
	int fd=open("Scfifo",O_RDWR);		
	int shmid[s+1];
	char *buffer[s+1];
	int i;
	for(i=1;i<=s;i++)
	{
		int key=1236+i;
		shmid[i]=shmget(key,100,0666|IPC_CREAT);
		buffer[i]=(char *)shmat(shmid[i],NULL,0);
	}
	shm=shmget(1235,sizeof(int),0666|IPC_CREAT);
	frees=(int *)shmat(shm,NULL,0);
	int sm3=shmget(1236,(s+1)*sizeof(int),0666|IPC_CREAT);
	int *pid=(int *)shmat(sm3,NULL,0);
	pid[0]=getpid();

	
	state=(int *)malloc(sizeof(int)*(s+1));
	//int i;
    for(i=1;i<=s;i++)
    	state[i]=0; 	
	while(1)
	{
		char msg[100];
		read(fd,msg,100);
		if((msg[0]>=65 && msg[0]<=90) || (msg[0]>=97 && msg[0]<=122) || (msg[0]>=48 && msg[0]<=57))
				//how to know if input is available or not by other than this method
		{
	//		printf("sc read %s\n",msg);
			int flag=0;
	//		printf("s \n");
			while(1)
			{
				 flag=0;
				 int i;
			for(i=1;i<=s;i++)
			{
				if(state[i]==0)
				{
					flag=i;
					break;
				}
			}
			if(flag!=0)
				break;
			}
			state[flag]=1;
			int i=0;
			while(msg[i]!='|')
				i++;
			msg[i]='\0';
			printf("sc read %s\n",msg);
			strcpy(buffer[flag],msg);
			 printf("sc wrote %s to shm \n",buffer[flag]);

			 kill(pid[flag],SIGUSR1);
		}
	}
}
