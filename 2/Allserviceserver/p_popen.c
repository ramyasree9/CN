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
	 strcpy(msg,"I am popen|");
		write(1,msg,strlen(msg));
		sleep(5+rand()%10);
	}
}
