#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
typedef struct{
	int id;
	int* index;
	char *string;
	int max;
	pthread_mutex_t *mtx;
	int *string_nr;
}data;

void *f(void *arg){
	data args=*((data*)arg);
	while(1){
		pthread_mutex_lock(args.mtx);
		if(*(args.string_nr)==args.max){
			printf("%d is exiting\n",args.id);
			break;
		}
		if(*(args.index)<128){
			int r=random()%24;
			args.string[*(args.index)]='a'+r;
			*(args.index)+=1;
		}
		pthread_mutex_unlock(args.mtx);
	}
	pthread_mutex_unlock(args.mtx);
	return NULL;
}
void *print(void *arg){
	data args=*((data*)arg);
	while(1){
		pthread_mutex_lock(args.mtx);
		if(*(args.index)==128){
			args.string[128]=0;
			printf("%s\n",args.string);
			memset(args.string,0,128*sizeof(char));
			*(args.index)=0;
			*(args.string_nr)+=1;
		}
		if(*(args.string_nr)==args.max){
			printf("Done printing, exiting\n");
			break;
		}
		pthread_mutex_unlock(args.mtx);
	}
	pthread_mutex_unlock(args.mtx);
	return NULL;
}
int main(int argc,char*argv[]){
	int n,m;
	scanf("%d",&n);
	scanf("%d",&m);
	pthread_t *th=malloc(sizeof(pthread_t)*(n+1));
	pthread_mutex_t *mtx=malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mtx,NULL);
	char *string=malloc(sizeof(char)*129);
	int *index=malloc(sizeof(int));
	*index=0;
	int *string_nr=malloc(sizeof(int));
	*string_nr=0;
	data *args=malloc(sizeof(data)*(n+1));
	for(int i=0;i<=n;i++){
		args[i].id=i;
		args[i].index=index;
		args[i].mtx=mtx;
		args[i].string=string;
		args[i].string_nr=string_nr;
		args[i].max=m;
		if(i==n)
			pthread_create(&th[i],NULL,print,&args[i]);
		else
			pthread_create(&th[i],NULL,f,&args[i]);
	}
	for(int i=0;i<=n;i++)
		pthread_join(th[i],NULL);
	pthread_mutex_destroy(mtx);
	free(mtx);
	free(args);
	free(index);
	free(string);
	free(string_nr);
	free(th);
	return 0;
}
