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

//int semid,semid1;
int *frees;
char *shm;
int *pid;
char arg[100];
void sig_hand()
{

			int no=atoi(arg);
	printf("in service %d\n",no);
	signal(SIGUSR1,sig_hand);
//	p(semid);
	printf("read from shm  %s\n",shm);
	int fd=open(shm,O_RDWR);
//	v(semid);
			char msg[100];
			sprintf(msg,"sevice %s is servicing a client ",arg);
			write(fd,msg,strlen(msg));
			sleep(5);
			*frees=no;
			kill(pid[0],SIGUSR2);
}
int main(int argc,char *argv[])
{
	signal(SIGUSR1,sig_hand);
	printf("SERVICE PROGRAM %s  PID  %d\n",argv[1],getpid());
	strcpy(arg,argv[1]);
	int s=atoi(argv[2]);
	int sm3=shmget(1236,(s+1)*sizeof(int),0666);
	pid=(int *)shmat(sm3,NULL,0);

	pid[atoi(argv[1])]=getpid();
	int key=atoi(argv[1])+1236;
	int shmid=shmget(key,100,0666);
	shm=(char *)shmat(shmid,(char *)0,0);
	int shmid1=shmget(1235,sizeof(int),0666);
	frees=(int *)shmat(shmid1,(char *)0,0);
	while(1)
	{
		
	}
}
