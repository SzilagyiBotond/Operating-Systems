#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
	pthread_barrier_t *barrier;
	pthread_mutex_t *mtx;
	int id;
	int m;
}data;
void *f(void* arg){
	data args=*((data*)arg);
	printf("%d is waiting to start\n",args.id);
	pthread_barrier_wait(args.barrier);
	for(int i=0;i<args.m;i++){
		pthread_mutex_lock(&args.mtx[i]);
		printf("%d is at the checkpoint %d\n",args.id,i+1);
		usleep(1000000);
		pthread_mutex_unlock(&args.mtx[i]);
	}
	return NULL;
}
int main(int argc, char*argv[]){
	int n=atoi(argv[1]);
	int m=atoi(argv[2]);
	pthread_mutex_t *mtx=malloc(sizeof(pthread_mutex_t)*m);
	for(int i=0;i<m; i++){
		pthread_mutex_init(&mtx[i],NULL);
	}
	pthread_barrier_t *barrier=malloc(sizeof(pthread_barrier_t));
	pthread_barrier_init(barrier,NULL,n);
	data *args=malloc(sizeof(data)*n);
	pthread_t *th=malloc(sizeof(pthread_t)*n);
	for(int i=0;i<n;i++){
		args[i].mtx=mtx;
		args[i].barrier=barrier;
		args[i].id=i+1;
		args[i].m=m;
		pthread_create(&th[i],NULL,f,&args[i]);
	}
	for(int i=0;i<n;i++){
		pthread_join(th[i],NULL);
	}
	pthread_barrier_destroy(barrier);
	for(int i=0;i<m;i++)
		pthread_mutex_destroy(&mtx[i]);
	free(mtx);
	free(barrier);
	free(th);
	free(args);
	return 0;
}
