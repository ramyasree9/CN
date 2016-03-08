#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <poll.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
		int pp[2];
		pipe(pp);
		FILE *fin[4];
		fin[0]=popen("./p2","r");
		fin[1]=popen("./p3","r");
		fin[2]=popen("./p4","r");
		fin[3]=popen("./p5","r");
		FILE *fout;
		int fd;
		fout=popen("./p6","w");
		fd=fileno(fout);
		struct pollfd pfds[5];
		int i;
		for(i=0;i<4;i++)
		{	
			pfds[i].fd=fileno(fin[i]);
			pfds[i].events=POLLIN;
		}
		struct pollfd pf[1];
		pf[0].fd=pp[0];
		pf[0].events=POLLIN;
		int ret=0;
		char buffer[100];
		int c=fork();
		if(c==0)
		{
			close(pp[0]);
			dup2(pp[1],1);
			char buffer[100];
			while(1)
			{
			//	printf("child|");
				strcpy(buffer,"i_am_p1|");
				write(1,buffer,strlen(buffer));
				sleep(rand()%10);
			}
		}
		else
		{
			close(pp[1]);
		while(1)
		{
			ret=poll(pfds,4,0);
			if(ret>0)
			{
			//	printf("sthng\n");
				for(i=0;i<4;i++)
				{
					if(pfds[i].revents==POLLIN)
					{
		//				printf("yes\n");
						read(pfds[i].fd,buffer,100);
						int k=0;
						while(buffer[k]!='\0' && buffer[k]!='|')
							k++;
						buffer[k+1]='\0';
						write(fd,buffer,k+1);
					}
				}
			}
			else
			{
			//	printf("polling pipe\n");
				int r=poll(pf,1,0);
				if(r>0)
				{
				//	printf("poll pipe success\n");
					read(pp[0],buffer,100);
					int k=0;
						while(buffer[k]!='\0' && buffer[k]!='|')
							k++;
						buffer[k+1]='\0';
					write(fd,buffer,k+1);
				}
			}
		}
		}
		

}