#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
typedef struct{
	pthread_mutex_t *mtx;
	int id;
	int* n;
} data;

void* func(void* arg){
	data args=*((data*)arg);
	while(1){
		pthread_mutex_lock(args.mtx);
		if(abs(*args.n)>500){
			printf("%d thread recieved %d and is stopping\n",args.id,*args.n);
			pthread_mutex_unlock(args.mtx);
			break;	
		}
		int a=random() % 1001-500;
		*args.n+=a;
		printf("%d generated %d\n",args.id,*args.n);
		pthread_mutex_unlock(args.mtx);
		sleep(1);
	}
	return NULL;
}
int main(int argc,char* argv[]){
	srandom(getpid());
	pthread_mutex_t *mtx=malloc(sizeof(pthread_mutex_t));
	int* n=malloc(sizeof(int));
	pthread_t *th=malloc(3*sizeof(pthread_t));
	*n=0;
	data *args=malloc(3*sizeof(data));
	pthread_mutex_init(mtx,NULL);
	for(int i=0;i<3;i++){
		args[i].mtx=mtx;
		args[i].n=n;
		args[i].id=i;
		pthread_create(&th[i],NULL,func,&args[i]);
	}
	for(int i=0;i<3;i++)
		pthread_join(th[i],NULL);
	pthread_mutex_destroy(mtx);
	free(mtx);
	free(th);
	free(args);
	free(n);
	return 0;
}
