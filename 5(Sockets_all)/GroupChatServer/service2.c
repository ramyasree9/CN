#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/ipc.h>
#include <sys/select.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <poll.h>
#include <ctype.h>
#define maxc 10


pthread_t tid[maxc];
pthread_mutex_t lock;
int c=0;
int nsfd[maxc];
void *chat()
{
	printf("chatting\n");
	int i=0;
	fd_set rfds;
	int maxfd=0;
	char buffer[100];
	int ret;
	struct timeval tv;
	while(1)
	{
		FD_ZERO(&rfds);
	//	pthread_mutex_lock(&lock);
		int no=c;
	//	pthread_mutex_unlock(&lock);
		int j;
		for(i=0;i<no;i++)
		{

		FD_SET(nsfd[i],&rfds);
		if(maxfd<nsfd[i])
			maxfd=nsfd[i];
		}

		tv.tv_sec=0;
		tv.tv_usec=10;
		ret=select(maxfd+1,&rfds,NULL,NULL,&tv);
		if(ret>0)
		{
			for(i=0;i<no;i++)
			{
				if(FD_ISSET(nsfd[i],&rfds))
				{
					strcpy(buffer,"");
					recv(nsfd[i],buffer,100,0);
					int kl=0;
					while(buffer[kl]!='\0' && buffer[kl]!='|')
						kl++;
					buffer[kl+1]='\0';
					for(j=0;j<no;j++)
					{
						if(j!=i)
						{
							printf("sending from %d to %d\n",i,j);
							send(nsfd[j],buffer,strlen(buffer),0);
						}
					}
				}
			}
		}

	}
}
int main(int argc,char *argv[])
{
	printf("entered\n");
	pthread_mutex_init(&lock,NULL);

	//printf("%d\n", argc);
	//printf("%s\n", argv[0]);
	//printf("%s\n", argv[1]);
	int shmid=shmget(1234,2*sizeof(int),06666);
	int *sfd=(int *)shmat(shmid,NULL,0);
//	printf("from shm %d %d \n",sfd[0],sfd[1] );
	nsfd[c]=sfd[1];
	c++;

	struct sockaddr_in client_addrs[maxc];
	int addrs_len[maxc];
	
	pthread_t first;
	pthread_create(&first,NULL,chat,NULL);

		while(1)
		{
			addrs_len[c]=sizeof(struct sockaddr_in);
			nsfd[c]=accept(sfd[0],(struct sockaddr *)&client_addrs[c],&addrs_len[c]);
			printf("accepted %d\n", nsfd[c]);
		//	printf("next stmnt\n");
		//	pthread_mutex_lock(&lock);
			c++;
		//	pthread_mutex_unlock(&lock);
		//	printf("done\n");
		}
	//	pthread_exit(NULL);

}