#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(int argc,char* argv[]){
	if(argc<2){
		perror("Too few arguments");
		exit(0);
	}
	FILE* f=fopen(argv[1],"r");
	int c2p[2];
	pipe(c2p);
	if(fork()==0){
		close(c2p[0]);
		char* buf=malloc(100*sizeof(char));
		while(fread(buf,1,100*sizeof(char),f)>0){
			int len=strlen(buf);
			for(int i=0;i<len-1;i++){
				if(buf[i]=='.' && buf[i+1]>='a' && buf[i+1]<='z')
					buf[i+1]+='A'-'a';
			}
			write(c2p[1],buf,100*sizeof(char));
			memset(buf,0,100*sizeof(char));
		}
		free(buf);
		close(c2p[1]);
		fclose(f);
		exit(0);
	}
	close(c2p[1]);
	char* buf=malloc(100*sizeof(char));
	while(read(c2p[0],buf,100*sizeof(char))>0){
		printf("Reading from child\n");
		printf("%s",buf);
		memset(buf,0,100*sizeof(char));
	}
	free(buf);
	close(c2p[0]);
	wait(0);
	fclose(f);
	return 0;
}
