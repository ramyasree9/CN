#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <string.h>
int sfd,client_addrs_len[10];
struct sockaddr_in client_addrs[10];
int my_id;
int c=0;
int nsfd[10];
int *freed;
int *pid;	//pids of platforms
void handler2()
{
	signal(SIGUSR2,handler2);
	printf("some train arrived \n");
}
void handler()
{
	signal(SIGUSR1,handler);
	client_addrs_len[c]=sizeof(struct sockaddr_in);
	//while(nsfd==-1)
	{

	 nsfd[c]=accept(sfd,(struct sockaddr*)&client_addrs[c],&client_addrs_len[c]);
	}
	printf("platform %d accepted  and got nsfd as %d\n",my_id ,nsfd[c]);
	char buffer[100];
	int r=recv(nsfd[c],buffer,100,0);
	close(nsfd[c]);
	c++;
	if(r==-1)
	{
		perror("recv error");
	}
	printf("pf %d received size %d:",my_id ,r);
	printf("%s\n",buffer);
	//write(1,buffer,r);
	sleep(5);
	*freed=my_id;
	kill(pid[0],SIGUSR2);
}
int main(int argc,char *argv[])
{
	signal(SIGUSR1,handler);
	signal(SIGUSR2,handler2);
	if(argc!=2)
	{
		printf("enter correct no of arguments (cmd line)\n");
		exit(0);
	}
	int shmid1=shmget(1235,sizeof(int),0666|IPC_CREAT);
	freed=(int *)shmat(shmid1,NULL,0);
	int shmid=shmget(1234,4*sizeof(int),0666|IPC_CREAT);
	pid=(int *)shmat(shmid,NULL,0);
	my_id=atoi(argv[1]);
	pid[my_id]=getpid();
	int Smid=pid[0];

	char comp[100];
	int port;
	if(my_id==1)
	{
		port=6050;
	}
	else if(my_id==2)
	{
		port=6060;
	}
	else
		port=6070;
	struct sockaddr_in my_addrs;
	my_addrs.sin_family=AF_INET;
	my_addrs.sin_addr.s_addr=INADDR_ANY;
	my_addrs.sin_port=htons(port);
	printf("creatind scoket on prt %d\n",port );
	sfd=socket(AF_INET,SOCK_STREAM,0);
	printf("got sfd as %d\n", sfd);
	bind(sfd,(struct sockaddr *)&my_addrs,sizeof(struct sockaddr_in));
	listen(sfd,10);
	printf("ready to listen\n");
	while(1)
	{

	}

}