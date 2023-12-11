#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char* argv[]){
	int a2b[2],b2a[2];
	pipe(a2b);
	pipe(b2a);
	srandom(getpid());
	if(fork()==0){
		close(a2b[0]);
		close(b2a[1]);
		int n=random()%200+50;
		while(1){
			if(n%2==0){
				write(a2b[1],&n,sizeof(int));
			}
			else{
				n=n+1;
				write(a2b[1],&n,sizeof(int));
			}
			printf("A writes to B %d\n",n);
			read(b2a[0],&n,sizeof(int));
			printf("A reads from B %d\n",n);
			if(n<5)
				break;
		}
		close(a2b[1]);
		close(b2a[0]);
		exit(0);
	}
	if(fork()==0){
		close(a2b[1]);
		close(b2a[0]);
		int n;
		while(1){
			read(a2b[0],&n,sizeof(int));
			printf("B reads froma A %d\n",n);
			n=n/2;
			write(b2a[1],&n,sizeof(int));
			printf("B writes to A %d\n",n);
			if(n<5)
				break;
		}
		close(a2b[0]);
		close(b2a[1]);
		exit(0);
	}
	close(a2b[1]);
	close(a2b[0]);
	close(b2a[1]);
	close(b2a[0]);
	wait(0);wait(0);
	return 0;
}
