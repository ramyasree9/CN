#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
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
	int sm1=shmget(1234,sizeof(int),0666);
	int sm2=shmget(1235,sizeof(int),0666);
	int sem1=semget(1236,1,0666);
	int sem2=semget(1237,1,0666);

	int *x,*y;
	x=(int *)shmat(sm1,NULL,0);
	y=(int *)shmat(sm2,NULL,0);
	
	int c=2;
	sleep(4);
	
	while(1)
	{
 	  p(sem1);
	  printf("x= %d \n",*x);
	  c=*x+1;
	  *y=c;
	  sleep(3);
      	  v(sem2);
	}
	
	
}
