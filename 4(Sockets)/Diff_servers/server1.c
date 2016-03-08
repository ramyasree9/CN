#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
int main()
{
	char buf[100];
	int d=read(0,buf,100);
//	char buf[100];
	int i=0;
	while(i<d)
	{
		if(buf[i]!=' ')
		printf("%c",toupper(buf[i]));
		else
		printf(" ");
		i++;
	}
	//write(1,buf,strlen(buf));
}