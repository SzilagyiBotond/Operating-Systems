#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
int main(int argc, char* argv[]){
	int s2d[2];
	int d2s[2];
	pipe(s2d);
	pipe(d2s);
	srandom(getpid());
	int d=fork();
	if(d==-1){
		perror("Cannot fork fam");
		exit(1);
	}
	if(d==0){
		close(d2s[0]);
		close(s2d[1]);
		int recieved,sent;
		while(1){
			sent=random()% 10 + 1;
			write(d2s[1],&sent,sizeof(int));
			printf("Daughter sends %d\n",sent);
			if(sent==10)
			break;
			read(s2d[0],&recieved,sizeof(int));
			printf("Daughter recieves %d\n",recieved);
			if(recieved==10)
			break;
		}
		close(d2s[1]);
		close(s2d[0]);
		exit(0);
	}
	int s=fork();
	if(s==-1){
		perror("Cannot fork fam");
		exit(1);
	}
	if(s==0){
		close(d2s[1]);
		close(s2d[0]);
		int recieved,sent;
		while(1){
			read(d2s[0],&recieved,sizeof(int));
			printf("Son recieved %d\n",recieved);
			if(recieved==10)
				break;
			sent=random()% 10 + 1;
			write(s2d[1],&sent,sizeof(int));
			printf("Son sent %d\n",sent);
			if(sent==10)
			break;
		}
		close(d2s[0]);
		close(s2d[1]);
		exit(0);
	}
	close(s2d[1]);
	close(s2d[0]);
	close(d2s[1]);
	close(d2s[0]);
	wait(0);
	wait(0);
	return 0;
}
