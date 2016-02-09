#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/select.h>
#include <errno.h>
#include <ctype.h>
char buffer[1000];
void sig_hand()
{
	/* code below is for writing to pout using popen  */

//	printf("handling signal buffer till now is %s\n",buffer);
	signal(SIGUSR1,sig_hand);
	//if(strcmp(buffer,"") && ret!=-1)
	{
		FILE *fp=popen("./p_out","w");		//popen in signal function is not working chekc in a separate code for its working
	//sleep(2);
		strcat(buffer,"|");
	printf("signal handler writing buffer as %s\n",buffer );
	int fd=fileno(fp);
	write(fd,buffer,strlen(buffer));
	sleep(4);
	strcpy(buffer,"");

	}
	
	


}
int main()
{
	int id=getpid();
	printf("ALL SERVCICE SERVER PROGRAM	%d \n",id);
	strcpy(buffer,"");
	signal(SIGUSR1,sig_hand);
	mkfifo("Fifo",0666);
	int ffd=open("Fifo",O_RDWR);		//rdonly
	int no=4;
	FILE *f=popen("./p_popen","r");
	int pofd=fileno(f);
	int pfd[2];
	fd_set rfds;
	struct timespec tv;
	pipe(pfd);
	
	FD_ZERO(&rfds);
	FD_SET(ffd,&rfds);
	FD_SET(pfd[0],&rfds);
	FD_SET(0,&rfds);
	FD_SET(pofd,&rfds);

	sigset_t blockset;

    sigemptyset(&blockset);         /* Block SIGINT */
    sigaddset(&blockset, SIGUSR1);

	int max=ffd;
	if(max<pfd[0])
		max=pfd[0];
	if(max<0)
		max=0;
	if(max<pofd)
		max=pofd;
	max++;

	int pid=fork();
	if(pid==0)
	{
//		printf("child proc \n");
		close(pfd[0]);
	//	printf("enter msg to write to pipe\n");
		dup2(pfd[1],1);
		execv("p_pipe",NULL);
	}
	else
	{
//		printf("parent proc \n");
		close(pfd[1]);
		while(1)
	{
		FD_ZERO(&rfds);
	FD_SET(ffd,&rfds);
	FD_SET(pfd[0],&rfds);
	FD_SET(0,&rfds);
	FD_SET(pofd,&rfds);
	tv.tv_sec=1;
	tv.tv_nsec=0;
			//printf("parent is polling\n");
	 int ret=pselect(max,&rfds,NULL,NULL,&tv,&blockset);
	if(ret==-1)
		perror("sel error");
	else if(ret)
	{
	//	printf("ready\n");
		int i;
	//	for(i=0;i<no;i++)
		{
			if(FD_ISSET(0,&rfds))
			{
				printf("parent is reading\n");
				char in[100];
				int m=read(0,in,100);
				int h=0;
				i=0;
				while(in[i]!='\0' && in[i]!='|')
					i++;
				in[i]='\0';
				strcat(buffer," ");
				strcat(buffer,in);
			}
			if(FD_ISSET(ffd,&rfds))
			{
				printf("parent is reading\n");
				char in[100];
				int m=read(ffd,in,100);
				int h=0;
				i=0;
				while(in[i]!='\0' && in[i]!='|')
					i++;
				in[i]='\0';
				strcat(buffer," ");
				strcat(buffer,in);
			}
			if(FD_ISSET(pofd,&rfds))
			{
				printf("parent is reading\n");
				char in[100];
				int m=read(pofd,in,100);
				int h=0;
				i=0;
				while(in[i]!='\0' && in[i]!='|')
					i++;
				in[i]='\0';
				strcat(buffer," ");
				strcat(buffer,in);
			}
			if(FD_ISSET(pfd[0],&rfds))
			{
				printf("parent is reading\n");
				char in[100];
				int m=read(pfd[0],in,100);
				int h=0;
				i=0;
				while(in[i]!='\0' && in[i]!='|')
					i++;
				in[i]='\0';
				strcat(buffer," ");
				strcat(buffer,in);
			}
		}
	}
	}
	}
	
	
}
