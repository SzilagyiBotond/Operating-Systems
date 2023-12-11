#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
int rule(int game){
	if(game%7==0 || game%3==0)
		return 1;
	int save=game;
	while(save>0){
		int i=save%10;
		if(i==7 || i==3)
			return 1;
		save=save/10;
	}
	return -1;
}
void boltz(int nr,int n,int p[][2]){
	int game;

	for(int i=0;i<n;i++){
		if(nr==n-1){
			if(i!=nr && i!=nr-1){
				close(p[i][1]);
				close(p[i][0]);
			}
			close(p[nr-1][1]);
			close(p[nr][0]);
			while(1){
				read(p[nr-1][0],&game,sizeof(int));
				if(game==-1){
					write(p[nr][1],&game,sizeof(int));
					printf("Child %d said someone failed\n",nr);
					break;
				}
				sleep(1);
				int guess=random()%6+1;
				if(guess==1){
					game=-1;
					write(p[nr][1],&game,sizeof(int));
					printf("%d failed\n",nr);
					break;
				}
				game++;
				int to_say=rule(game);
				if(to_say==-1)
					printf("Child %d said %d\n",nr,game);
				if(to_say==1)
					printf("Child %d said boltz\n",nr);
				write(p[nr][1],&game,sizeof(int));
			}
		}
		else{
			if(fork()==0){
				boltz(nr+1,n,p);
			}
			if(i!=nr && i!=nr-1){
				close(p[i][1]);
				close(p[i][0]);
			}
			close(p[nr-1][1]);
			close(p[nr][0]);
			while(1){
				read(p[nr-1][0],&game,sizeof(int));
				if(game==-1){
					write(p[nr][1],&game,sizeof(int));
					printf("Child %d said someone failed\n",nr);
					break;
				}
				sleep(1);
				int guess=random()%6+1;
				if(guess==1){
					game=-1;
					write(p[nr][1],&game,sizeof(int));
					printf("%d failed\n",nr);
					break;
				}
				game++;
				int to_say=rule(game);
				if(to_say==-1)
					printf("Child %d said %d\n",nr,game);
				if(to_say==1)
					printf("Child %d said boltz\n",nr);
				write(p[nr][1],&game,sizeof(int));
			}

			wait(0);
		}
		close(p[nr-1][0]);
		close(p[nr][1]);
		exit(0);
	}
}
int main(int argc,char* argv[]){
	int n;
	printf("What is n: ");
	scanf("%d",&n);
	int p[n][2];
	int game=1;
	for(int i=0;i<n;i++){
		pipe(p[i]);
	}
	if(fork()==0){
		boltz(1,n,p);	
	}
	for(int i=0;i<n;i++){
		if(i!=0 && i!=n-1){
			close(p[i][1]);
			close(p[i][0]);
		}
	}
	close(p[0][0]);
	close(p[n-1][1]);
	printf("Parent said %d\n",game);
	while(1){

		write(p[0][1],&game,sizeof(int));
		read(p[n-1][0],&game,sizeof(int));
		if(game==-1){
			printf("Parent said someone failed\n");			
			break;
		}
		sleep(1);
		int r=random()%6+1;
		if(r==1){
			game=-1;
			write(p[0][1],&game,sizeof(int));
			printf("Parent failed\n");
			break;
		}
		game++;
		int to_say=rule(game);
		if(to_say==-1)
			printf("Parent said %d\n",game);
		if(to_say==1)
			printf("Parent said boltz\n");
	}
	close(p[0][1]);
	close(p[n-1][0]);
	wait(0);
	return 0;
}
