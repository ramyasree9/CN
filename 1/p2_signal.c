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
int *pid;
int c;
int *x,*y;
void sig_hand2()
{

	signal(SIGUSR2,sig_hand2);  
	printf("x=%d\n",*x);
	c=*x+1;
	*y=c;
	sleep(2);
	kill(pid[0],SIGUSR1); 

}
int main()
{
 	int sm1=shmget(1234,sizeof(int),0666);
	int sm2=shmget(1235,sizeof(int),0666);

	x=(int *)shmat(sm1,NULL,0);
	y=(int *)shmat(sm2,NULL,0);
	
	int sm4=shmget(1236,2*sizeof(int),0666);

	pid=(int *)shmat(sm4,NULL,0);
	
	
 	pid[1]=getpid();
	signal(SIGUSR2,sig_hand2);
	
	c=1;
	*y=c;
	while(1)
	{
		
	}
	
}
