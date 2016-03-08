#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>
#include <pthread.h>
#include <poll.h>
#include <ctype.h>
char buffer[1000];
int sfd;
int nsfd[100];
int child_pid[50];
int child_fd[50];
int ec=0;
int present[100];
struct sockaddr_in client_addrs[100];
int client_addrs_len[100];
int c=0;
void handler()
{
	signal(SIGCHLD,handler);
	int pid=wait(NULL);
	int i=0;
	for(i=0;i<=ec;i++)
	{
		if(child_pid[i]==pid)
		{
			present[child_fd[i]]=1;
			break;
		}
	}

}
void sig_hand()
{
	/* code below is for writing to pout using popen  */

//	printf("handling signal buffer till now is %s\n",buffer);
	signal(SIGUSR1,sig_hand);
	int np=0;
	int first_client;
	for(np=0;np<=c;np++)
	{
		if(present[np]==1)
		{
			first_client=np;
			break;
		}
	}
	int cc=fork();
	if(cc==0)
	{
		dup2(nsfd[first_client],1);
		execv("echo",NULL);
	}
	else
	{
		present[first_client]=0;
		child_pid[ec]=cc;
		child_fd[ec]=first_client;
		ec++;
	}

}
void *accept_fun()
{
	while(1)
	{
		client_addrs_len[c]=sizeof(struct sockaddr_in);
		nsfd[c]=accept(sfd,(struct sockaddr *)&client_addrs[c],&client_addrs_len[c]);
		present[c]=1;
		c++;
	}
}
int main()
{
	signal(SIGCHLD,handler);
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
	struct pollfd pfds[no];
	pipe(pfd);
	pfds[0].fd=ffd;
	pfds[1].fd=pfd[0];
	pfds[2].fd=0;
	pfds[3].fd=pofd;
	pfds[0].events=POLLIN;
	pfds[1].events=POLLIN;
	pfds[2].events=POLLIN;
	pfds[3].events=POLLIN;

	struct sockaddr_in my_addrs;
	memset(&my_addrs,0,sizeof(struct sockaddr_in));
	int port=6020;
	my_addrs.sin_family=AF_INET;
	my_addrs.sin_addr.s_addr=INADDR_ANY;
	my_addrs.sin_port=htons(port);
	sfd=socket(AF_INET,SOCK_STREAM,0);
	bind(sfd,(struct sockaddr *)&my_addrs,sizeof(struct sockaddr_in));
	listen(sfd,10);

	pthread_t tid;
	pthread_create(&tid,NULL,accept_fun,NULL);

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
				int j=0;
				while(in[j]!='\0' && in[j]!='|')
					j++;
				in[j+1]='\0';
		//		write(1,"Alls read",9);
		//		write(1,in,m);
			//	strcat(buffer," ");
			//	strcat(buffer,in);
				//strcat(buffer,"\n");
			//	printf("so buffer became %s \n",buffer);
				int np=0;
				for(np=0;np<=c;np++)
				{
					if(present[np]==1)
					send(nsfd[np],in,j+1,0);
				}
			}
		}
	}
	}
	}
	
	
}
