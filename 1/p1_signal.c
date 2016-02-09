#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int * pid,c;
int *x,*y;
void sig_hand1()
{
	signal(SIGUSR1,sig_hand1);  
	printf("y=%d\n",*y);
	c=*y+1;
	*x=c;
	sleep(2);
	kill(pid[1],SIGUSR2); 
}
int main()
{
 	int sm1=shmget(1234,sizeof(int),0666|IPC_CREAT);
	int sm2=shmget(1235,sizeof(int),0666|IPC_CREAT);

	x=(int *)shmat(sm1,NULL,0);
	y=(int *)shmat(sm2,NULL,0);
	
	int sm3=shmget(1236,2*sizeof(int),0666|IPC_CREAT);

	pid=(int *)shmat(sm3,NULL,0);
	
	signal(SIGUSR1,sig_hand1);
	
 	pid[0]=getpid();
	c=0;
//	while(1)
	{
	//	*x=c;
	//	kill(pid,SIGUSR1);
		*x=c;
		sleep(2);
		raise(SIGUSR1);
 		
	}
	while(1)	
	{
	
	}
}
