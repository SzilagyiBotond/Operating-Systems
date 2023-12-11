#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
typedef struct{
	char* string;
	pthread_mutex_t *mtx;
	int* letters;
	int id;	
}data;

void*f(void*a){
	data arg=*((data*)a);
	//printf("Id %d\n",arg.id);
	//printf("%s\n",arg.string);
	pthread_mutex_lock(arg.mtx);
	for(int i=0;i<strlen(arg.string);i++){
		if(arg.string[i]>='a' && arg.string[i]<='z'){
			arg.letters[arg.string[i]-'a']+=1;
		}
	}
	pthread_mutex_unlock(arg.mtx);
	return NULL;
}
int main(int argc, char* argv[]){
	printf("%s\n",argv[0]);
	pthread_mutex_t *mtx=malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mtx,NULL);
	pthread_t *th=malloc((argc-1)*sizeof(pthread_t));
	data *args=malloc((argc-1)*sizeof(pthread_t));
	int* letters=malloc(26*sizeof(int));
	memset(letters,0,26*sizeof(int));
	for(int i=0;i<argc-1;i++){
		args[i].string=malloc((1+strlen(argv[i+1])*sizeof(char)));
		args[i].string[strlen(argv[i+1])]=0;		
		args[i].id=i;
		args[i].letters=letters;
		args[i].mtx=mtx;
		args[i].string=argv[i+1];
		printf("%s",args[i].string);
		pthread_create(&th[i],NULL,f,&args[i]);
	}
	for(int i=0;i<argc-1;i++)
		pthread_join(th[i],NULL);
	pthread_mutex_destroy(mtx);
	free(mtx);	
for(int i=0;i<26;i++)
		printf("%d\n",letters[i]);
	for(int i=0;i<argc-1;i++){
		free(args[i].string);
	}	
	printf("Strings freed\n");
	free(letters);
	free(args);
	free(th);
	return 0;
}

