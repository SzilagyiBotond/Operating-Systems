#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
int main(int argc,char* argv[]){
	int n;
	printf("What is n: ");
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		int f=fork();
		if(f==-1){
			perror("Error on fork");
			exit(1);
		}
		if(f==0){
			printf("Child id %d Child pid %d Parent Pid %d\n",i,getpid(),getppid());
			exit(0);
		}
		printf("In parent - Child id %d Child pid %d Parent Pid %d\n",i,f,getpid());
	}
	for(int i=0;i<n;i++){
		wait(0);
	}
	return 0;
}
