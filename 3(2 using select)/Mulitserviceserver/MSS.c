#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <errno.h>
#include <sys/select.h>
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
	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(fd,&rfds);
	struct timeval tv;
	char a[100];
	int max=fd+1;	
	while(1)
	{
		char msg[100];
		tv.tv_sec=1;
		tv.tv_usec=0;
		FD_ZERO(&rfds);
		FD_SET(fd,&rfds);
		int ret=select(max,&rfds,NULL,NULL,&tv);
		if(ret==-1)
		{
			perror("select error\n");
		}
	    else if(ret)
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
