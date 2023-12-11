#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
typedef struct{
	int id;
	int M;
	pthread_mutex_t* mtx;
	pthread_barrier_t* barrier;
}data;

void* f(void* arg){
	data args=*((data*)arg);
	printf("%d is waiting to start\n",args.id);
	pthread_barrier_wait(args.barrier);
	for(int i=0;i<args.M;i++){
		pthread_mutex_lock(&args.mtx[i]);
		printf("%d reached checkpoint %d\n",args.id,i);
		sleep(1);
		pthread_mutex_unlock(&args.mtx[i]);
	}
	printf("%d finished the race\n",args.id);
	return NULL;
}
int main(int argc, char* argv[]){
	int n=atoi(argv[1]);
	int m=atoi(argv[2]);
	pthread_t *th=malloc(sizeof(pthread_t)*n);
	pthread_mutex_t* mtx=malloc(sizeof(pthread_mutex_t)*m);
	pthread_barrier_t* barrier=malloc(sizeof(pthread_barrier_t));
	data *args=malloc(sizeof(data)*n);
	pthread_barrier_init(barrier,NULL,n);
	for(int i=0;i<m;i++)
		pthread_mutex_init(&mtx[i],NULL);
	for(int i=0;i<n;i++){
		args[i].id=i;
		args[i].M=m;
		args[i].mtx=mtx;
		args[i].barrier=barrier;
		pthread_create(&th[i],NULL,f,&args[i]);
	}
	for(int i=0;i<n;i++)
		pthread_join(th[i],NULL);

	printf("Race is finished\n");
	free(barrier);
	for(int i=0;i<m;i++)
		pthread_mutex_destroy(&mtx[i]);
	free(mtx);
	free(args);
	free(th);
	return 0;
}
