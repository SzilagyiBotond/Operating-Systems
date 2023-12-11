#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int main(int argc,char*argv[]){
	if(argc<0)
	{
		perror("Too few arguments");
		exit(1);
	}
	if(argc>11){
		perror("Too many arguments");
		exit(1);
	}
	int pc[argc-1][2];
	for(int i=0;i<argc-1;i++){
		pipe(pc[i]);
	}
	int total_len=0;
	for(int i=0;i<argc-1;i++){
		total_len+=strlen(argv[i+1]);
		if(fork()==0){
			for(int j=0;j<argc-1;j++){
				if(j!=i)
				{
					close(pc[j][1]);
					close(pc[j][0]);
				}
				close(pc[j][0]);}
			int len=strlen(argv[i+1]);
			for(int k=0;k<len;k++){
				if(argv[i+1][k]>='a' && argv[i+1][k]<='z')
					argv[i+1][k]+='A'-'a';
			}
			write(pc[i][1],&len,sizeof(int));
			write(pc[i][1],argv[i+1],len*sizeof(char));
			close(pc[i][1]);
			exit(0);
		}
	}
	for(int i=0;i<argc-1;i++)
		close(pc[i][1]);
	char* result=malloc((total_len+1)*sizeof(char));
	for(int i=0;i<argc-1;i++)
	{
		int len;
		read(pc[i][0],&len,sizeof(int));
		printf("The size of the argument %d\n",len);
		char* buf=malloc((len+1)*sizeof(char));
		read(pc[i][0],buf,len*sizeof(char));
buf[len]=0;		
strcat(result,buf);
		free(buf);
		wait(0);
	}
	printf("%s",result);
	free(result);
	return 0;
}
