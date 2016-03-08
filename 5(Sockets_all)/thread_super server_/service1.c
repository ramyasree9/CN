#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <poll.h>
#include <ctype.h>
#define maxc 10


pthread_t tid[maxc];
int c=0;
int nsfd[maxc];
void *service_others(void *sfd)
{
	printf("new thread created\n");
	int nsfd=*(int *)sfd;
//	printf("my nsfd is %d\n",nsfd );
	while(1)
		{
			sleep(4);
			char buffer[100],buf[100];
			strcpy(buffer,"");
		//	printf("before read\n");
			struct pollfd fds[1];
			fds[0].fd=nsfd;
			fds[0].events=POLLIN;
			int ret=poll(fds,1,0);
			while(ret<=0)
			{
				ret=poll(fds,1,0);
			}
			read(nsfd,buffer,100);
		//	printf("after read\n");
				strcpy(buf,"service 1 recieved:");
				strcat(buf,buffer);
				printf("-----\n");
				printf("%s\n",buf );
				printf("---\n");
		//	write(nsfd,buf,strlen(buf));
		}
}
void *service_first()
{
//	printf("first client enetered\n");
	while(1)
	{
		char buf[100];
	char in[100];
	sleep(4);
	int d=read(0,buf,100);
	buf[d]='\0';
	strcpy(in,"service 1 received");
	strcat(in,buf);
	write(1,in,strlen(in));
	//	sleep(rand()%10);
	}
}

int main(int argc,char *argv[])
{
	printf("entered\n");

	//printf("%d\n", argc);
	//printf("%s\n", argv[0]);
	//printf("%s\n", argv[1]);
	int shmid=shmget(1234,sizeof(int),06666);
	int *sfd=(int *)shmat(shmid,NULL,0);
//	printf("from shm %d\n",*sfd );
	struct sockaddr_in client_addrs[maxc];
	int addrs_len[maxc];
	
	pthread_t first;
	pthread_create(&first,NULL,service_first,NULL);

		while(1)
		{
			addrs_len[c]=sizeof(struct sockaddr_in);
			nsfd[c]=accept(*sfd,(struct sockaddr *)&client_addrs[c],&addrs_len[c]);
	//		printf("accepted %d\n", nsfd[c]);
			pthread_create(&tid[c],NULL,service_others,(int *)&nsfd[c]);
			c++;
		}
		pthread_exit(NULL);

}