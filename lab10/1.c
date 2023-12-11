#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
int main(int argc, char* argv[])
{
	int p[2];
	if(argc<2)
	{
		perror("No arguments");
		exit(1);
	}
	if(pipe(p)<0)
	{
		perror("Error creating the pipe");
		exit(1);
	}
	int f=fork();
	if(f<0)
	{
		perror("Error creating the fork");
		exit(1);
	}
	else if(f==0)
	{
		close(p[0]);
		int save_out=dup(1);
		if(dup2(p[1],1)<0)
		{
			perror("Error on dup 2");
			exit(2);
		}
		if(execvp(argv[1],argv+1)==-1)
		{
			dup2(save_out,1);
			perror("Error on execvp");
			exit(2);
		}
		exit(0);
	}
	else{
		close(p[1]);
		int buff_size=100;
		char* buf=malloc(sizeof(char)*buff_size);
		memset(buf,0,buff_size*sizeof(char));
		int k;
		while(0<(k=read(p[0],buf,(buff_size-1))))
		{
			printf("%s",buf);
			memset(buf,0,buff_size*sizeof(char));
		}
		free(buf);
		wait(NULL);
		close(p[0]);
	}
	return 0;
}
