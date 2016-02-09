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
#include <poll.h>
int main()
{
		char filename[100];
		scanf("%s",filename);
		int fd=open(filename,O_RDWR);
		char name[100];
		printf("service 2 is servicing its client through fifo: %s\n",filename);
	//	scanf("%s",name);
	//	printf("service read client fifo as%s\n",filename);
		strcpy(name,"service 2 servcied client|");
		write(fd,name,strlen(name));
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
