#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char* argv[]){
	int a2b=mkfifo("./a2b",0600);
	if(a2b<0){
perror("Cannot create fifo");
exit(1);
}
	a2b=open("./a2b",O_WRONLY);
	if(a2b<0){
	perror("Cannot open fifo");
	exit(1);
}
	while(1){
		printf("What is the command: \n");
		char* command=malloc(2000*sizeof(char));
		memset(command,0,2000*sizeof(char));
		int k=read(0,command,2000*sizeof(char));
		command[k-1]=0;
		if(strcmp(command,"stop")==0)
			break;
		FILE* f=popen(command,"r");
		char* buf=malloc(2000*sizeof(char));
		while(fread(buf,1,1999,f)>0){
			int nr=strlen(buf);
			write(a2b,&nr,sizeof(int));
			write(a2b,buf,nr*sizeof(char));
			memset(buf,0,2000*sizeof(char));
		}
		pclose(f);
		free(command);
		free(buf);
	}
	int msg=-1;
	write(a2b,&msg,sizeof(int));
	close(a2b);
	unlink("./a2b");
	return 0;
}
