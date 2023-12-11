#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
int main(int argc,char* argv[]){
	int pc[2];
	pipe(pc);
	int cp[2];
	pipe(cp);
	int f=fork();

	if(f==-1){
		perror("Cannot fork");
		exit(1);
	}
	if(f==0){
		int n;
		close(pc[1]);
		close(cp[0]);
		read(pc[0],&n,sizeof(int));
		int average;
		for(int i=0;i<n;i++)
		{
			int aux;
			read(pc[0],&aux,sizeof(int));
			average+=aux;
		}
		average=average/n;
		write(cp[1],&average,sizeof(int));
		close(cp[1]);
		close(pc[0]);
		exit(0);
	}
	int n;
	close(pc[0]);
	close(cp[1]);
	printf("What is n: ");
	scanf("%d",&n);
	srandom(getpid());
	write(pc[1],&n,sizeof(int));
	for(int i=0;i<n;i++){
		int aux=random()%10;
		printf("The number %d is %d\n",i,aux);
		write(pc[1],&aux,sizeof(int));
	}
	int average;
	read(cp[0],&average,sizeof(int));
	printf("The average is %d\n",average);
	wait(0);
	close(pc[1]);
	close(pc[0]);
	return 0;
}
