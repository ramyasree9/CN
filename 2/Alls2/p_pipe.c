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
	while(1)
	{
	char msg[100];
	//printf("enter msg to write to pipe\n");
	int r=read(0,msg,100);
	write(1,msg,r);
	}
}
