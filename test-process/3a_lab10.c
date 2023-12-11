#include <sys/types.h>

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc,char* argv[]){
	int a2b=open("./ab",O_WRONLY);
	if(a2b<0){
		perror("Cannto open fifo from A to B");
		exit(1);
	}
	int c2a=open("./ca",O_RDONLY);
	if(c2a<0){
		close(a2b);
		perror("Cannot open fifo from C to A");
		exit(1);
	}
	srandom(getpid());
	int n=random()% (1000-100)+100;
	while(1){
		if(write(a2b,&n,sizeof(int))<0){
			perror("Cannot write");
			exit(2);
		}
		printf("A writing to B %d\n",n);
		if(read(c2a,&n,sizeof(int))<0){
			perror("Cannot read");
			exit(2);
		}
		printf("A reading from C %d\n",n);
		if(n<10)
			break;
		else
			n++;
	}
	close(a2b);
	close(c2a);
	return 0;
}
