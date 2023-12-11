#include <stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
int main(int argc,char* argv[])
{
	int c2p[2];
	if(pipe(c2p)==-1)
	{
		perror("Error on pipe");
		exit(1);
	}
	int f=fork();
	if(0>f){
		perror("Error on fork");
		exit(1);
	}
	else if(0==f)
	{
		dup2(c2p[1],1);
		close(c2p[0]);
		if(-1==execvp(argv[1],argv+1))
		{
			close(c2p[1]);
			perror("Error on exec");
			exit(1);
		}
		close(c2p[1]);
		exit(0);
	}
	close(c2p[1]);
	int k;
	char* buf=malloc(sizeof(char)*101);
	memset(buf,0,sizeof(char)*101);
	while((k=read(c2p[0],buf,sizeof(char)*100))>0)
	{	buf[k]=0;
		printf("%s",buf);
		memset(buf,0,sizeof(char)*101);
	}
	free(buf);
	close(c2p[0]);
	wait(NULL);
	return 0;
}
