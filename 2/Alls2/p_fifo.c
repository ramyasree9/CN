#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
	int fd=open("Fifo",O_RDWR);		//wronly
	while(1)
	{
	char msg[100];
	printf("enter a msg to write into fifo \n");
	read(0,msg,100);
	write(fd,msg,strlen(msg));
	}
}
