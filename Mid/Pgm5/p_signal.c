#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
int main()
{
	int fd=open("Fifo",O_RDWR);		//wronly
	int pid;
	while(1)
	{
	printf("enter process id to send a signal \n");
	scanf("%d",&pid);
	kill(pid,SIGUSR1);
	}
}
