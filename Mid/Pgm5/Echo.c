#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main()
{

	char buffer[100];
	strcpy(buffer,"echo_server_now|");
	int c=0;
	while(1)
	{
		c++;
		sleep(rand()%5);
		write(1,buffer,strlen(buffer));
		if(c==7)
			break;
	}
}