#include <stdio.h>
#include <unistd.h>

#include <stdlib.h>
#include <string.h>
int main()
{	
	char buffer[100];
//	printf("p2 created\n");
	while(1)
	{
		strcpy(buffer,"i_am_p3|");
		write(1,buffer,strlen(buffer));
		sleep(rand()%9);
	}
}