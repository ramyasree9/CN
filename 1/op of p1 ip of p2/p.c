#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
	char s[100];
	strcpy(s,"./");
	strcat(s,argv[1]);
        int no=argc-1;
	char a[100];
	a[0]=no+'0';
	a[1]='\0';
	strcpy(argv[0],a);
	int i=0;
	//for(i=0;i<=no;i++)
	//printf("%s \n",argv[i]);
//printf("%s \n",s);
	FILE * fd=popen(s,"w");
 	//fwrite(a,strlen(a),1,fd);
	i=0;
	for(i=0;i<argc;i++)
	{
//	printf("writing\n");
	fprintf(fd,"%s",argv[i]);
	fprintf(fd,"%s","\n");
//	printf("written\n");
	//i++;
	}
	pclose(fd);
}
