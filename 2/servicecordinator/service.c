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

int semid,semid1;

char *shm,*shm1;
int *pid;
char arg[100];
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
void sig_hand()
{
	printf("in service 1\n");
	signal(SIGUSR1,sig_hand);
//	p(semid);
	printf("read from shm  %s\n",shm);
	int fd=open(shm,O_RDWR);
//	v(semid);
			char msg[100];
			sprintf(msg,"sevice %s is servicing a client ",arg);
			write(fd,msg,strlen(msg));
			sleep(5);
			int no=atoi(arg);
			if(no==1)
				kill(pid[0],SIGALRM);
			else
				kill(pid[0],SIGCHLD);
}
void sig_hand1()
{
	printf("in service 2\n");
	signal(SIGUSR2,sig_hand1);
//	p(semid);
	printf("read from shm  %s\n",shm1);
	int fd=open(shm1,O_RDWR);
//	v(semid);
			char msg[100];
			sprintf(msg,"sevice %s is servicing a client ",arg);
			write(fd,msg,strlen(msg));
			sleep(5);
			int no=atoi(arg);
			if(no==1)
				kill(pid[0],SIGALRM);
			else
				kill(pid[0],SIGCHLD);
}
int main(int argc,char *argv[])
{
	signal(SIGUSR1,sig_hand);
	signal(SIGUSR2,sig_hand1);
	printf("SERVICE PROGRAM %s  PID  %d\n",argv[1],getpid());
//	printf("enter pid of SC \n");
//	scanf("%d",&pid);
	strcpy(arg,argv[1]);
	//synchronize and write pid to shm 
	int shmid=shmget(1234,100,0666);
	semid=semget(1235,1,0666);
	int shmid1=shmget(1237,100,0666);

	int sm3=shmget(1236,3*sizeof(int),0666);
	pid=(int *)shmat(sm3,NULL,0);

	pid[atoi(argv[1])]=getpid();

	shm=(char *)shmat(shmid,(char *)(0),0);
	shm1=(char *)shmat(shmid1,(char *)(0),0);

	// char pid[100];
	// sprintf(pid,"%d",getpid());
	while(1)
	{
		
		// if((shm[0]>=65 && shm[0]<=90) || (shm[0]>=97 && shm[0]<=122) || (shm[0]>=48 && shm[0]<=57))
		// {
		// 	int fd=open(shm,O_RDWR);
		// 	char msg[100];
		// 	spritnf(msg,"sevice %s is servicing a client ",argv[1]);
		// 	write(fd,msg,strlen(msg));
		// 	int no=atoi(argv[1]);
		// 	if(no==1)
		// 		kill(pid,SIGINT);
		// 	else
		// 		kill(pid,SIGCHLD);
		// 	sleep(4);
		// }
		// char name[100];
		// printf("service entered");
		// scanf(" %s",name);
		// printf("service read client fifo as%s\n",name);
		// int fd=open(name,O_RDWR);
		// // provide a service or differnt service by threads or by programs
		// char filename[100];	
		// read(fd,filename,100);
		// printf("service read client file as %s\n",filename);
		// int f=open(filename,O_RDONLY);
		// char buffer[1000];	
		// int n=read(f,buffer,1000);
		// printf("service read file contents as %s\n",buffer);
		// write(fd,buffer,n);
	}
}
