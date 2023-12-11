#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
int f;
void child_handler(int sig){
	printf("Child process terminating\n");
	exit(0);
}
void parent_handler(int sig){
	printf("Parent terminating\n");
	kill(f,SIGUSR1);
	wait(0);
	exit(0);
}
void zombie_handler(int sig){
	printf("Parent waiting for children\n");
	wait(0);
}
int main(int argc,char* argv[]){
	f=fork();
	if(f==0){
		signal(SIGUSR1,child_handler);
		while(1){
			printf("Child working...\n");
			sleep(3);
		}

	}
	signal(SIGUSR1,parent_handler);
	signal(SIGCHLD,zombie_handler);
	for(int i=0;i<3;i++){
		printf("Parent working\n");
		sleep(2);
	}
	kill(getpid(),SIGUSR1);

	return 0;
}
