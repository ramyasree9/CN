#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
int main()
{
	char buf[100];
	printf("service2 servicing ");
	int d=read(0,buf,100);
	write(1,buf,d);
	printf("\n");
//	char buf[100];
	int i=0;
	//buf[d]='\0';
	//char buffer[100];
// remthis //	strcpy(buffer,"service 1 served ");
//	int l=strlen(buffer);
// renmove//	strcat(buffer,buf);
//rem//	write(1,buffer,strlen(buffer));
	
	sleep(5);
	printf("service2 finished servicing ");
	write(1,buf,d);
	printf("\n");

}