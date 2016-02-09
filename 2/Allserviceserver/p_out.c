#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <poll.h>
int main()
{
	/*		code below is for reading from a popen  remove while loop*/
	// while(1)
	{
		char msg[1000];
		printf("proc is reading msg for ALLS\n");
		read(0,msg,1000);
		printf(" proc read %s \n",msg);
	 }

}
