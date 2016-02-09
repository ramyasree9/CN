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
#include <poll.h>
#include <ctype.h>
char buffer[1000];
void sig_hand()
{
	/* code below is for writing to pout using popen  */

	printf("handling signal buffer till now is %s\n",buffer);
	signal(SIGUSR1,sig_hand);
	FILE *fp=popen("./p_out","w");		//popen in signal function is not working chekc in a separate code for its working
	//sleep(2);
	printf("signal handler writing buffer as %s\n",buffer );
	 // fprintf(fp,"%s",buffer);
	 // fprintf(fp,"%s","\n");
	//fwrite(buffer,strlen(buffer),1,fp);
	 int fd=fileno(fp);
	 write(fd,buffer,strlen(buffer));
	sleep(4);
//	int dumfd=open("ffd",O_RDWR);
//	char dum[1000];
//	read(dumfd,dum,1000);
//	printf("signal fun read %s\n",dum);
//	printf("signal proc wrote into out \n");
	strcpy(buffer,"");

	/* 	code be;ow is for writing to pout using pipe ande exec*/
	// printf("in signal handler \n");
	// int f=fork();
	// int outp[2];
	// pipe(outp);
	// if(f>0)
	// {
	// 	//wait(NULL);
	// 	close(outp[0]);
	// 	write(outp[1],buffer,strlen(buffer));
	// }
	// else{
	// 	sleep(4);
	// 	close(outp[1]);
	// 	dup2(outp[0],0);
	// 	execv("p_out",NULL);

	// }

	/* code below for writing to a fifo */
 	// int fd=open("outfifo",O_RDWR);
 	// write(fd,buffer,strlen(buffer));
 	// strcpy(buffer,"");

}
int main()
{
	int id=getpid();
	printf("ALL SERVCICE SERVER PROGRAM	%d \n",id);
	strcpy(buffer,"");
	signal(SIGUSR1,sig_hand);
	mkfifo("Fifo",0666);
	int ffd=open("Fifo",O_RDWR);		//rdonly
	int no=2;
	int pfd[2];
	struct pollfd pfds[no];
	pipe(pfd);
	pfds[0].fd=ffd;
	pfds[1].fd=pfd[0];
	pfds[0].events=POLLIN;
	pfds[1].events=POLLIN;

	int pid=fork();
	if(pid==0)
	{
//		printf("child proc \n");
		close(pfd[0]);
		printf("enter msg to write to pipe\n");
		dup2(pfd[1],1);
	//	execlp("p_pipe","p_pipe",NULL);
		execv("p_pipe",NULL);
	}
	else
	{
//		printf("parent proc \n");
		close(pfd[1]);
		while(1)
	{
			//printf("parent is polling\n");
	int ret=poll(pfds,no,3000);
	if(ret)
	{
	//	printf("ready\n");
		int i;
		for(i=0;i<no;i++)
		{
			if(pfds[i].revents!=0)
			{
				printf("parent is reading\n");
				char in[100];
				int m=read(pfds[i].fd,in,100);
				int h=0;
				while(in[i]!='|')
					i++;
				in[i]='\0';
				write(1,"Alls read",9);
				write(1,in,m);
				strcat(buffer,in);
				//strcat(buffer,"\n");
				printf("so buffer became %s \n",buffer);
			}
		}
	}
	}
	}
	
	
}
