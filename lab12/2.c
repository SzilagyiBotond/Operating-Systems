#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct{
	char* string;
	int id;
	int* frequency;
	pthread_mutex_t *mtx;
}data;

void* f(void* arg){
	data args=*((data*)arg);
	for(int i=0;i<strlen(args.string);i++){
		if(args.string[i]>='a' && args.string[i]<='z'){
			pthread_mutex_lock(args.mtx);
			args.frequency[args.string[i]-'a']++;
			pthread_mutex_unlock(args.mtx);
		}
	}
	return NULL;
}
int main(int argc, char* argv[]){
	int nr=argc-1;
	pthread_mutex_t *mtx=malloc(sizeof(pthread_mutex_t));
	pthread_t *th=malloc(sizeof(pthread_t)*nr);
	pthread_mutex_init(mtx,NULL);
	data *args=malloc(sizeof(data)*nr);
	int* frequency=malloc(sizeof(int)*('z'-'a'+1));
	for(int i=0;i<nr;i++){
		args[i].id=i;
		args[i].frequency=frequency;
		args[i].string=argv[i+1];
		args[i].mtx=mtx;
		pthread_create(&th[i],NULL,f,&args[i]);
	}
	for(int i=0;i<nr;i++)
		pthread_join(th[i],NULL);
	for(int i=0;i<('z'-'a'+1);i++)
		printf("%d ---- %c\n",frequency[i],('a'+i));
	pthread_mutex_destroy(mtx);
	free(mtx);
	free(args);
	free(frequency);
	free(th);
	return 0;
}
