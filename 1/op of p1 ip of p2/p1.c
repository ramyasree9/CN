#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	 char s[100];
	 sleep(2);
	 scanf("%s",s);
	 int no=atoi(s);
	printf("read %d",no);
	 int i=0;
	 char argv[no+1][100];
	for(i=0;i<no;i++)
	 {
		scanf("%s",argv[i]);
		printf("%s \n",argv[i]);
		
	 }
	 printf("%s read %d \n",argv[0],no);
	 no--;
	 if(no!=0)
	 {
		 strcpy(s,"./");
		 strcat(s,argv[1]);
		printf("%s is next\n",s);
		char a[100];
		a[0]=no+'0';
		a[1]='\0';
		 i=1;
		 FILE * fd=popen(s,"w");
		 fprintf(fd,"%s",a);
		fprintf(fd,"%s","\n");
		for(i=1;i<=no;i++)
		{
		fprintf(fd,"%s",argv[i]);
		fprintf(fd,"%s","\n");
		}
		 //write(1,a,strlen(a));
 pclose(fd);
	}

		
	
}
