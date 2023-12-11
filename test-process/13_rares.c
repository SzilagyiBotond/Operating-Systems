#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc,char* argv[]){
	int n;
	printf("What is n: ");
	scanf("%d",&n);
	int a2b[2],b2c[2],c2a[2];
	pipe(a2b);pipe(b2c);pipe(c2a);
	if(fork()==0){
		close(b2c[1]);
		close(b2c[0]);
		close(a2b[0]);
		close(c2a[1]);
		int* nr=malloc(sizeof(int)*n);
		for(int i=0;i<n;i++){
			printf("What is the number: ");
			scanf("%d",nr+i);
			printf("%d\n",nr[i]);
		}
		for(int i=0;i<n;i++){
			write(a2b[1],&nr[i],sizeof(int));
			printf("A sends to B %d\n",nr[i]);
		}
		free(nr);
		int sum;
		read(c2a[0],&sum,sizeof(int));
		printf("A reads from C %d\n",sum);
		close(c2a[0]);
		close(a2b[1]);
		exit(0);
	}
	if(fork()==0){
		close(c2a[1]);
		close(c2a[0]);
		close(a2b[1]);
		close(b2c[0]);
		srandom(getpid());
		for(int i=0;i<n;i++){
			int nr;
			read(a2b[0],&nr,sizeof(int));
			printf("B reads from A %d\n",nr);
			int r=random()%5+2;
			nr+=r;
			write(b2c[1],&nr,sizeof(int));
			printf("B writes to C %d\n",nr);
		}
		close(b2c[1]);
		close(a2b[0]);
		exit(0);
	}
	if(fork()==0){
		close(a2b[1]);
		close(a2b[0]);
		close(c2a[0]);
		close(b2c[1]);
		int result=0;
		for(int i=0;i<n;i++){
			int aux;
			read(b2c[0],&aux,sizeof(int));
			result+=aux;
			printf("C reads from B %d\n",aux);
		}
		write(c2a[1],&result,sizeof(int));
		printf("C writes to A %d\n",result);
		exit(0);
	}
	close(a2b[1]);
	close(a2b[0]);
	close(c2a[0]);
	close(b2c[1]);
	close(c2a[1]);
	close(b2c[0]);
	wait(0);wait(0);wait(0);
	return 0;
}
