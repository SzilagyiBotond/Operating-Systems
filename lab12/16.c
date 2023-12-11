#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
typedef struct{
	pthread_mutex_t *mtx;
	int *digits;
	int number;
}data;

void *f(void* arg){
	data args=*((data*)arg);
	int save=args.number;
	while(save>0){
		pthread_mutex_lock(args.mtx);
		int dig=save%10;
		save=save/10;
		args.digits[dig]+=1;
		pthread_mutex_unlock(args.mtx);
	}
	return NULL;
}

int main(int argc,char* argv[]){
	int size=argc-1;
	pthread_mutex_t *mtx=malloc(sizeof(pthread_mutex_t));
	pthread_t *th=malloc(size*sizeof(pthread_t));
	data *args=malloc(size*sizeof(data));
	int *digits=malloc(10*sizeof(int));
	memset(digits,0,10*sizeof(int));
	for(int i=0;i<size;i++){
		args[i].mtx=mtx;
		args[i].number=atoi(argv[i+1]);
		args[i].digits=digits;
		pthread_create(&th[i],NULL,f,&args[i]);
	}
	for(int i=0;i<size;i++){
		pthread_join(th[i],NULL);
	}
	for(int i=0;i<9;i++){
		printf("%d -- %d\n",i,digits[i]);
	}
	free(mtx);
	free(digits);
	free(args);
	free(th);
	return 0;
}
