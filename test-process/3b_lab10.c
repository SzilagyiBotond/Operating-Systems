#include <sys/types.h>

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc,char* argv[]){
	int a2b=open("./ab",O_RDONLY);
	if(a2b<0){
		perror("Cannot open A to B");
		exit(1);
	}
	int b2c=open("./bc",O_WRONLY);
	if(b2c<0){
		close(a2b);
		perror("Cannot open B to C");
		exit(1);
	}
	int n;
	while(1){
		if(read(a2b,&n,sizeof(int))<0)
		{
			perror("Cannot read");
			exit(2);
		}
		printf("Reading from A to B %d\n",n);
		if(n>=10){
			n*=2;
		}
		if(write(b2c,&n,sizeof(int))<0){
			perror("Cannot write");
			exit(1);
		}
		printf("Writing from B to C %d\n",n);
		if(n<10){
			break;
		}
	}
	close(a2b);
	close(b2c);
	return 0;
}
