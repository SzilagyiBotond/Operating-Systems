#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc,char* argv[]){
	int a2d[2],b2d[2],c2d[2],d2b[2],d2c[2];
srandom(getpid());	
pipe(a2d);
	pipe(b2d);
	pipe(c2d);
	pipe(d2b);
	pipe(d2c);
	if(fork()==0){
		close(a2d[1]);close(b2d[1]);close(c2d[1]);close(d2b[0]);close(d2c[0]);
		int n;
		read(a2d[0],&n,sizeof(int));
		printf("D reads from A %d\n",n);
		while(1){
			int b;
			read(b2d[0],&b,sizeof(int));
			printf("D reads from B %d\n",b);
			int c;
			read(c2d[0],&c,sizeof(int));
			printf("D reads from C %d\n",c);
			int guess;
			if(abs(c-b)<n){
				guess=1;
			}
			else{
				guess=-1;
			}
			write(d2b[1],&guess,sizeof(int));
			write(d2c[1],&guess,sizeof(int));
			if(guess==1)
				break;
		}
		close(a2d[0]);close(b2d[0]);close(d2c[1]);close(d2b[1]);close(c2d[0]);
		exit(0);
	}
	if(fork()==0){
		close(a2d[1]);close(a2d[0]);close(b2d[0]);close(c2d[1]);close(c2d[0]);close(d2b[1]);close(d2c[0]);close(d2c[1]);
		while(1){
			int n=random()%200+150;
			write(b2d[1],&n,sizeof(int));
			printf("B sends to D %d\n",n);
			int guess;
			read(d2b[0],&guess,sizeof(int));
			if(guess==1)
				break;
		}
		close(b2d[1]);
		close(d2b[0]);
		exit(0);
	}
	if(fork()==0){
		close(a2d[1]);close(a2d[0]);close(b2d[0]);close(b2d[1]);close(c2d[0]);close(d2b[1]);close(d2b[0]);close(d2c[1]);
		while(1){
			int n=random()%200+150;
			write(c2d[1],&n,sizeof(int));
			printf("C sends to D %d\n",n);
			int guess;
			read(d2c[0],&guess,sizeof(int));
			if(guess==1)
				break;
		}
		close(c2d[1]);
		close(d2c[0]);
		exit(0);
	}
	close(b2d[1]);close(c2d[1]);close(d2b[0]);close(d2c[0]);
	close(b2d[0]);close(c2d[0]);close(d2b[1]);close(d2c[1]);
	close(a2d[0]);
	int n=random()%40+25;
	write(a2d[1],&n,sizeof(int));
	printf("Paren sent to D %d\n",n);
	wait(0);wait(0);wait(0);
	return 0;
}
