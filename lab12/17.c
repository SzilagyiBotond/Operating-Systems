#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
typedef struct{
	pthread_mutex_t *mtx;
	pthread_cond_t *cond;
	int n;
	int *array;
	int *index;
	int id;
}data;

void *f(void* arg){
	data args=*((data*)arg);
	while(1){
		pthread_mutex_lock(args.mtx);
		while(args.id!=*(args.index)%2)
			pthread_cond_wait(args.cond,args.mtx);
		if(*(args.index)>=args.n){
printf("%d is exiting\n",args.id);
*(args.index)+=1;			
break;
}
		int r=(random()%40)*2+args.id;
		args.array[*(args.index)]=r;
		printf("%d generates %d\n",args.id,r);
		*(args.index)+=1;
		pthread_cond_signal(args.cond);
		pthread_mutex_unlock(args.mtx);
	}
	pthread_cond_signal(args.cond);
	pthread_mutex_unlock(args.mtx);
	return NULL;
}
int main(int argc, char* argv[]){
	pthread_mutex_t *mtx=malloc(sizeof(pthread_mutex_t));
	pthread_cond_t *cond=malloc(sizeof(pthread_cond_t));
	int n;
	scanf("%d",&n);
	int *array=malloc(sizeof(int)*n);
	pthread_t *th=malloc(sizeof(pthread_t)*2);
	data *args=malloc(sizeof(data)*2);
	int *index=malloc(sizeof(int));
	*index=0;
	pthread_mutex_init(mtx,NULL);
	pthread_cond_init(cond,NULL);
	for(int i=0;i<2;i++){
		args[i].id=i;
		args[i].mtx=mtx;
		args[i].cond=cond;
		args[i].array=array;
		args[i].index=index;
		args[i].n=n;
		pthread_create(&th[i],NULL,f,&args[i]);
	}
	for(int i=0;i<2;i++)
		pthread_join(th[i],NULL);
	pthread_mutex_destroy(mtx);
	pthread_cond_destroy(cond);
	free(args);
	free(th);
	free(cond);
	free(mtx);
	free(array);
	free(index);
	return 0;
}
