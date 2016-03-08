#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
int main()
{
	char buf[100];
	char in[100];
	strcpy(in,"service1:");
//	printf("service1: \n");
	int d=read(0,buf,100);
//	char buf[100];
	buf[d]='\0';
	strcat(in,buf);
// remthis //	strcpy(buffer,"service 1 served ");
//	int l=strlen(buffer);
// renmove//	strcat(buffer,buf);
//rem//	write(1,buffer,strlen(buffer));
	write(1,in,strlen(in));
}