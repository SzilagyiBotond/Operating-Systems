#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc,char* argv[]){
	int a2b=mkfifo("./a2b",0600);
	if(a2b==-1){
		perror("Cannot create fifo");
		exit(1);
	}
	int b2a=mkfifo("./b2a",0600);
	if(b2a==-1){
		unlink("./a2b");
		perror("Cannot create fifo");
		exit(1);
	}
	a2b=open("./a2b",O_WRONLY);
	b2a=open("./b2a",O_RDONLY);
	srandom(getpid());
	while(1){
		int sent,recieved;
		sent=random()%10+1;
		write(a2b,&sent,sizeof(int));
		printf("A is sending %d\n",sent);
		if(sent==10)
			break;
		read(b2a,&recieved,sizeof(int));
		printf("A recieved %d\n",recieved);
		if(recieved==10)
			break;
	}
	close(a2b);
	close(b2a);
	unlink("./a2b");
	unlink("./b2a");
	return 0;
}
