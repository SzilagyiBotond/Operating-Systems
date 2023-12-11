#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
int main(int argc,char* argv[]){
	if(argc<2){
		perror("Too few arguments");
		exit(1);
	}
	struct timeval t1,t2;
	gettimeofday(&t1,NULL);
	int f=fork();
	if(f==-1){
		perror("Cannot fork");
		exit(1);
	}
	else if(f==0){
		execvp(argv[1],argv+1);
		exit(0);
	}
	printf("Ayyoo\n");
	wait(0);
	gettimeofday(&t2,NULL);
	printf("The exec time of the bash is %f\n",(double)(t2.tv_usec - t1.tv_usec) / 1000000 + (double) (t2.tv_sec - t1.tv_sec));
	return 0;
}
