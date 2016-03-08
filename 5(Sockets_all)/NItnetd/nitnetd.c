#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <signal.h>
#define ns 2
#define maxc 5

struct child_no
{
	pid_t pid;
	int sno; 
	int valid;
}plist[maxc];
//const int ns=2;
int occupy[ns],waitq[ns];
void hand()
{
	signal(SIGCHLD,hand);
	pid_t pid=wait(NULL);
	int ptr;
	for(ptr=0;ptr<maxc;ptr++)
	{
		if(plist[ptr].pid==pid)
		{
			plist[ptr].valid=0;
			occupy[plist[ptr].sno]--;
			waitq[plist[ptr].sno]--;
			break;
		}
	}
	//occupy[0]--;	
	//waitq[0]--;				//let us assume only 1 service has child later save  pids of childs and its requested service nos
}
int main()
{
	//2 services at present s1 limits clients to 1 and s2 to 2
	//extend this for more services and save child pids to know which child ended
	int ptr;
	for(ptr=0;ptr<maxc;ptr++)
		plist[ptr].valid=0;
	signal(SIGCHLD,hand);
	int sfd[ns],nsfd[ns];
	struct sockaddr_in my_addrs[2],client_addrs;
	int port[ns];
	int client_addrslen;
	port[0]=6000;
	port[1]=6020;
	int limit[ns];
	limit[0]=2;
	limit[1]=1;
	

	int i=0;

	int maxfd=0;
	fd_set rfds;
	struct timeval tv;
	tv.tv_usec=0;
	tv.tv_sec=2;
	FD_ZERO(&rfds);
	for(i=0;i<ns;i++)
	{	
		waitq[i]=0;
		occupy[i]=0;
	sfd[i]=socket(AF_INET,SOCK_STREAM,0);
	memset(&my_addrs[i],0,sizeof(struct sockaddr_in));
	my_addrs[i].sin_family = AF_INET;
	my_addrs[i].sin_addr.s_addr = INADDR_ANY;
	my_addrs[i].sin_port=htons(port[i]);
	bind(sfd[i],(struct sockaddr *)&my_addrs[i],sizeof(struct sockaddr_in));
	listen(sfd[i],limit[i]);
	FD_SET(sfd[i],&rfds);
	if(maxfd<sfd[i])
		maxfd=sfd[i];
	}

	
	//bzero((char *)&my_addrs,sizeof(my_addrs));
	

	while(1)
		{
			tv.tv_sec=2;
			FD_ZERO(&rfds);
			tv.tv_usec=3;
			maxfd=0;
			for(i=0;i<ns;i++)
			{
				if(waitq[i]==0 || (waitq[i]!=0 && occupy[i]<limit[i]))
				{
					if(sfd[i]>maxfd)
						maxfd=sfd[i];
					FD_SET(sfd[i],&rfds);
				}
			}
			int ret=select(maxfd+1,&rfds,NULL,NULL,&tv);
			if(ret>0)
			{
				for(i=0;i<ns;i++)
				{
					if(FD_ISSET(sfd[i],&rfds))
					{
						if(occupy[i]<limit[i])				//limit not reached ok...
						{
							occupy[i]++;
					//		printf("s avail %d\n",i );
							client_addrslen=sizeof(struct sockaddr_in);
							nsfd[i]=accept(sfd[i],(struct sockaddr *)&client_addrs,&client_addrslen);
							int cc=fork();
							if(cc==0)		//child
							{
						//		printf("child\n");
								int lp;
								for(lp=0;lp<ns;lp++)
							 	close(sfd[lp]);
							 	dup2(nsfd[i],0);
							// 	dup2(nsfd[i],1);		
							// 	dup2(nsfd[i],1);
							 //	dup2(pp[i][1],1);
							 	if(i==0)
							 	execv("service1",NULL);			//store these names in an array
							 	else
							 		execv("service2",NULL);
							}
							else			//parent
							{

									close(nsfd[i]);
									int ptr;
							for(ptr=0;ptr<maxc;ptr++)
							{
								if(plist[ptr].valid==0)
								{
									plist[ptr].valid=1;
									plist[ptr].pid=cc;
									plist[ptr].sno=i;
									break;
								}
							}
							}
						}
						else			//max no of clients are executing
						{
							
							waitq[i]++;
						}			//how to know child completed execution
		
					}
				}
			}
			
		}
}