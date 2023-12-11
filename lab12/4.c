#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
typedef struct{
	int id;
	int *index;
	int* array;
	int n;
	pthread_mutex_t *mtx;
	pthread_cond_t *cond;
}data;

void* f(void* arg){	
	data args=*((data*)arg);
	while(1){
		pthread_mutex_lock(args.mtx);
		while(args.id!=(*args.index)%2){
			pthread_cond_wait(args.cond,args.mtx);
		}
		if(*(args.index)>=args.n){
printf("%d is ending\n",args.id);			
*(args.index)+=1;
			break;
		}
		int r=(random()%50)*2+args.id;
		args.array[*(args.index)]=r;
		printf("%d generated %d\n",args.id,r);
		*args.index+=1;
		pthread_cond_signal(args.cond);
		pthread_mutex_unlock(args.mtx);
	}
	pthread_cond_signal(args.cond);
	pthread_mutex_unlock(args.mtx);
	return NULL;
}
int main(int argc, char* argv[]){
	int n=atoi(argv[1]);
	pthread_mutex_t *mtx=malloc(sizeof(pthread_mutex_t));
	pthread_cond_t *cond=malloc(sizeof(pthread_cond_t));
	srandom(getpid());
	pthread_mutex_init(mtx,NULL);
	pthread_cond_init(cond,NULL);
	pthread_t *th=malloc(sizeof(pthread_t)*2);
	int *index=malloc(sizeof(int));
	*index=0;
	int* array=malloc(sizeof(int)*n);
	data *args=malloc(sizeof(data)*2);
	for(int i=0;i<2;i++){
		args[i].id=i;
		args[i].index=index;
		args[i].array=array;
		args[i].cond=cond;
		args[i].mtx=mtx;
		args[i].n=n;
		pthread_create(&th[i],NULL,f,&args[i]);
	}
	for(int i=0;i<2;i++){
		pthread_join(th[i],NULL);
	}
	pthread_mutex_destroy(mtx);
	pthread_cond_destroy(cond);
	free(mtx);
	free(cond);
	free(th);
	free(array);
	free(args);
	free(index);
		return 0;
}
