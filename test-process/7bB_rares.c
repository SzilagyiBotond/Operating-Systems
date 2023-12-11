#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc,char* argv[]){
	int a2b=open("./a2b",O_RDONLY);
	int b2a=open("./b2a",O_WRONLY);
	srandom(getpid());
	while(1){
		int sent,recieved;
		read(a2b,&recieved,sizeof(int));
		printf("B recieved %d\n",recieved);
		if(recieved==10)
			break;
		sent=random()%10+1;
		write(b2a,&sent,sizeof(int));
		printf("B sent %d\n",sent);
		if(sent==10)
			break;
	}
	close(a2b);
	close(b2a);
	return 0;
}
