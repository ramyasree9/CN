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
void sig_hand()					// for now -service 1 sends signal sigint after completion
								// service 2 sends signal 
{
	signal(SIGALRM,sig_hand);
	state[1]=0;

}
void sig_hand1()					// for now -service 1 sends signal sigint after completion
								// service 2 sends signal 
{
	signal(SIGCHLD,sig_hand1);
	state[2]=0;
}
void p(int id)
{
	 struct sembuf sb;
	 sb.sem_num=0;
	 sb.sem_op=-1;
	 sb.sem_flg=0;
	 if((semop(id,&sb,1))==-1)    
	 {
	  perror("\nFailed to acquire semaphore.");
	  exit(0);
	 }
}
void v(int id)
{
	 struct sembuf sb;
	 sb.sem_num=0;
	 sb.sem_op=1;
	 sb.sem_flg=0;
	 if((semop(id,&sb,1))==-1)    
	 {
	  perror("\nFailed to release semaphore.");
	  exit(0);
	 }
}
int main()
{
	signal(SIGALRM,sig_hand);
	signal(SIGCHLD,sig_hand1);
	printf("SERVCICE COORDINATOR PROGRAM  %d \n",getpid());
	int n;
	printf("enter no of clients");
	scanf("%d",&n);
	int s;
	printf("enter no of services");
	scanf("%d",&s);
	mkfifo("Scfifo",0666);
	int fd=open("Scfifo",O_RDWR);		//rdonly
	int shmid=shmget(1234,100,0666|IPC_CREAT);
	int semid=semget(1235,1,0666|IPC_CREAT);

	int shmid1=shmget(1237,100,0666|IPC_CREAT);		//for serv2

	int sm3=shmget(1236,3*sizeof(int),0666|IPC_CREAT);
	int *pid=(int *)shmat(sm3,NULL,0);
	pid[0]=getpid();

	char *buffer,*buffer1;
    buffer=(char *)shmat(shmid,NULL,0);
     buffer1=(char *)shmat(shmid1,NULL,0);	//for serv2

	semctl(semid,0,SETVAL,1);
	state=(int *)malloc(sizeof(int)*(s+1));
	int i;
    for(i=1;i<=s;i++)
    	state[i]=0; 			//0  ==> free and 1 ==> busy
    //read all pids from shared memory
 //    sleep(4);			//wait for all services to enter their pids
 //    char buffer[1000];
 //    buffer=(char *)shmat(shmid,NULL,0);
 //    int pid[s+1];
	// int i=0;
	// while(i<strlen(buffer))			//complete this divide into tokens and fill pid array 
	// 								//shared mem erases or not 
	// 								// different processes write into shm and 1 proc read possible or not
	// {
	// 	char no[20];
	// 	char id[100];
	// 	int j=0;
	// 	while(buffer[i]!=' ')
	// 	{
	// 		no[j++]=buffer[i];
	// 		i++;
	// 	}
	// 	no[j]='\0';
	// 	i++;
	// 	j=0;
	// 	while(buffer[i]!='|')
	// 	{
	// 		id[j++]=buffer[i];
	// 		i++;
	// 	}
	// 	i++;
	// 	id[j]='\0';
	// 	int sno=atoi(no);
	// 	int val=atoi(id);
	// 	pid[sno]=val;
	// }
	// strcpy(buffer,"");
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
	//		int pid;
	//		printf("enter pid of servcie %d\n", flag);
	//		scanf("%d",&pid);
			int i=0;
			while(msg[i]!='|')
				i++;
			msg[i]='\0';
			printf("sc read %s\n",msg);
		//	p(semid);
			if(flag==1)
			strcpy(buffer,msg);			//assuming writing to buffer writes to shared memory
			else if(flag==2)
			strcpy(buffer1,msg);
		//	v(semid);
			if(flag==1)
			printf("sc wrote %s to shm \n",buffer);
			else if(flag==2)
			printf("sc wrote %s to shm \n",buffer1);

		//	sleep(3);					//wait for some time to write to shm before sending signal
			if(flag==1)					// or a single signal is sufficient or not ?!!
				kill(pid[flag],SIGUSR1);
			else if(flag==2)
				kill(pid[flag],SIGUSR2);
		}
	}
}
