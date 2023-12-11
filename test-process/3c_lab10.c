#include <sys/types.h>

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc,char* argv[]){
	int b2c=open("./bc",O_RDONLY);
	int c2a=open("./ca",O_WRONLY);
	if(b2c<0){
		perror("Cannot open B to C");
		exit(1);
	}
	if(c2a<0){
		close(b2c);
		perror("Cannot open C to A");
		exit(1);
	}
	int n;
	while(1){
		if(read(b2c,&n,sizeof(int))<0){
			perror("Cannot read");
			exit(2);
		}
		printf("Reading from B to C %d\n",n);
		if(n>=10){
			n=n/3;
		}
		if(write(c2a,&n,sizeof(int))<0){
			perror("Cannot write");
			exit(2);
		}
		printf("Writing from C to A %d\n",n);
		if(n<10)
			break;
	}
	close(b2c);
	close(c2a);
	return 0;
}
