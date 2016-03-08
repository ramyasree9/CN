#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main()
{	
	char buffer[100];
	printf("p6 created\n");
	while(1)
	{
		read(0,buffer,100);
		write(1,"p6:",4);
		int k=0;
		while(buffer[k]!='\0' && buffer[k]!='|')
			k++;
		buffer[k]='\0';
		write(1,buffer,k);
		printf("\n");
	}
}