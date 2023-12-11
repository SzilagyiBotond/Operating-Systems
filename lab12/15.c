#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
	int* letters;
	int* digits;
	pthread_mutex_t *mtx;
	char* string;
}data;

void *f(void* arg){
	data args=*((data*)arg);
	for(int i=0;i<strlen(args.string);i++){
		pthread_mutex_lock(args.mtx);
		if(args.string[i]>='a' && args.string[i]<='z'){
			*(args.letters)+=1;
		}
		if(args.string[i]>='0' && args.string[i]<='9'){
			*(args.digits)+=1;
		}
		pthread_mutex_unlock(args.mtx);
	}
	return NULL;
}
int main(int argc, char* argv[]){
	int size=argc-1;
	pthread_mutex_t *mtx=malloc(sizeof(pthread_mutex_t));
	pthread_t *th=malloc(size*sizeof(pthread_t));
	data *args=malloc(size*(sizeof(data)));
	int *letters=malloc(sizeof(int));
	int *digits=malloc(sizeof(int));
	pthread_mutex_init(mtx,NULL);
	*digits=0;
	*letters=0;
	for(int i=0;i<size;i++){
		args[i].mtx=mtx;
		args[i].string=argv[i+1];
		args[i].digits=digits;
		args[i].letters=letters;
		pthread_create(&th[i],NULL,f,&args[i]);
	}
	for(int i=0;i<size;i++){
		pthread_join(th[i],NULL);
	}
	printf("The number of letters %d\n",*(letters));
	printf("The number of digits %d\n",*(digits));
	pthread_mutex_destroy(mtx);
	free(args);
	free(digits);
	free(mtx);
	free(letters);
	free(th);
	return 0;
}
