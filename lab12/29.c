#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
typedef struct{
	pthread_mutex_t *mtx;
	pthread_barrier_t *barrier;
	int *array;
	int id;
	int n;
}data;

void *f(void* arg){
	data args=*((data*)arg);
	pthread_mutex_lock(args.mtx);
	int r=random()%11+10;
	args.array[args.id]=r;
	pthread_mutex_unlock(args.mtx);
	printf("%d is waiting\n",args.id);
	pthread_barrier_wait(args.barrier);
	while(1){
		pthread_mutex_lock(args.mtx);
		printf("%d is working\n",args.id);
		if(args.array[args.id]<0)
			break;
		int pos=0;
		for(int i=0;i<args.n;i++){
			if(args.array[i]>0 && i!=args.id)
				pos+=1;
		}
		if(pos==0)
			break;
		for(int i=0;i<args.n;i++){
			if(i!=args.id)
				args.array[i]-=1;
		}
		pthread_mutex_unlock(args.mtx);
	}
	pthread_mutex_unlock(args.mtx);
	return NULL;
}
int main(int argc, char*argv[]){
	int n;
	srandom(getpid());
	scanf("%d",&n);
	pthread_mutex_t *mtx=malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mtx,NULL);
	pthread_barrier_t *barrier=malloc(sizeof(pthread_barrier_t));
	pthread_barrier_init(barrier,NULL,n);
	pthread_t *th=malloc(sizeof(pthread_t)*n);
	int *array=malloc(sizeof(int)*n);
	data *args=malloc(sizeof(data)*n);
	for(int i=0;i<n;i++){
		args[i].n=n;
		args[i].id=i;
		args[i].array=array;
		args[i].barrier=barrier;
		args[i].mtx=mtx;
		pthread_create(&th[i],NULL,f,&args[i]);
	}
	for(int i=0;i<n;i++)
		pthread_join(th[i],NULL);
	for(int i=0;i<n;i++)
		printf("%d ",array[i]);
	printf("\n");
	free(args);
	pthread_barrier_destroy(barrier);
	pthread_mutex_destroy(mtx);
	free(barrier);
	free(mtx);
	free(th);
	free(array);
	return 0;
}

