#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <poll.h>
#include <ctype.h>
int main()
{
	printf("MULTI SERVCICE SERVER PROGRAM	\n");
	int n;
	// printf("enter no of clients");
	// scanf("%d",&n);
	int s=2;
	// printf("enter no of services");
	// scanf("%d",&s);
	int i;
	mkfifo("Mssf",0666);
	int fd=open("Mssf",O_RDWR);
	struct pollfd pfds[1];
	pfds[0].fd=fd;
	pfds[0].events=POLLIN;
	char a[100];	
	while(1)
	{
		char msg[100];
		int ret=poll(pfds,1,1000);
	    if(ret)
	    {
		read(fd,msg,100);
		printf("%s\n",msg);
		i=0;
		strcpy(a,msg);
		while(a[i]!='|')
			i++;
		a[i]='\0';
		char service[100];
		strcpy(service,"./service");
		strcat(service,a);
		char name[100];
		int j=0;
		i++;
		while(msg[i]!='|')
		{
			name[j++]=msg[i++];
		}
		name[j]='\0';
		printf("service name %s client fifo name %s \n",service,name);	
		FILE *fp=popen(service,"w");		//not checked for free or busy
		fprintf(fp,"%s",name);
		pclose(fp);
	    }
	    else
	    {
	    //	printf("no input\n");
	    }
	}
}
