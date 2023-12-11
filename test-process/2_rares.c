#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
void giving_birth(int n){
	if(n==1){
		printf("Last child\n");
		exit(0);
	}
	int f=fork();
	if(f==-1){
		perror("Cannot fork");
		exit(1);
	}
	if(f==0){
		printf("%d child\n",n);
		giving_birth(n-1);
		exit(0);
	}
	wait(0);
}
int main(int argc,char* argv[]){
	int n;
	printf("What is n: ");
	scanf("%d",&n);
	giving_birth(n);
	return 0;
}
