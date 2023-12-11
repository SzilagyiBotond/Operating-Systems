#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc,char* argv[]){
	int p2c[2],c2p[2];
	pipe(p2c);pipe(c2p);
	srandom(getpid());
	while(fork()==0){
		close(c2p[0]);
		close(p2c[1]);
		int p;
		int guess=-1;
		while(1){
			int c=random()%1000+100;
			read(p2c[0],&p,sizeof(int));
			printf("Child read %d\n",p);
			printf("Child generated %d\n",c);
			if(abs(p-c)<50)
				break;
			else{
				write(c2p[1],&guess,sizeof(int));			
			}
		}
		guess=1;
		write(c2p[1],&guess,sizeof(int));
		close(c2p[1]);
		close(p2c[0]);
		exit(0);
	}
	int count=0;
	close(p2c[0]);
	close(c2p[1]);
	int guess;
	while(guess!=1){
		count++;
		int r=random()%1050+50;
		write(p2c[1],&r,sizeof(int));
		read(c2p[0],&guess,sizeof(int));

	}
	printf("The count %d\n",count);
	close(p2c[1]);
	wait(0);
	return 0;
}
