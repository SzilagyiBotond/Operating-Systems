#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc,char* argv[]){
	if(argc<2){
		perror("Cannot create");
		exit(1);
	}
	int a2b=mkfifo("./a2b",0600);
	if(a2b==-1){
		perror("Cannot create fifo");
		exit(1);
	}
	int b2a=mkfifo("./b2a",0600);
	if(b2a==-1){
		unlink("./a2b");
		perror("Cannot create fifo");
		exit(1);
	}
	a2b=open("./a2b",O_WRONLY);
	b2a=open("./b2a",O_RDONLY);
	int total_len=0;
	for(int i=1;i<argc;i++){
		total_len+=strlen(argv[i]);
	}
	write(a2b,&argc,sizeof(int));
	char* result=malloc((total_len+1)*sizeof(char));
		for(int i=1;i<argc;i++){
			int len=strlen(argv[i]);
			write(a2b,&len,sizeof(int));
			write(a2b,argv[i],len*sizeof(char));
			char* buf=malloc((len+1)*sizeof(char));
			read(b2a,buf,len*sizeof(char));
			buf[len]=0;
			strcat(result,buf);
			free(buf);
		}
	result[total_len]=0;
	printf("%s\n",result);
	close(a2b);
	close(b2a);
	unlink("./a2b");
	unlink("./b2a");
	return 0;
}
