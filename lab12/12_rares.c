#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
typedef struct{
	pthread_mutex_t *mtx;
	int id;
	int* sum;
	int col;
	int** matrix;
}data;

void* f(void* arg){
	data args=*((data*)arg);
	pthread_mutex_lock(args.mtx);
	for(int i=0;i<args.col;i++){	
		*(args.sum)+=args.matrix[args.id][i];
	}
	pthread_mutex_unlock(args.mtx);
	return NULL;
}
int main(int argc,char* argv[]){
	FILE* file=fopen(argv[1],"r");
	int col=atoi(argv[3]);
	int row=atoi(argv[2]);
	printf("%d %d\n",row,col);	
	pthread_mutex_t *mtx=malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mtx,NULL);
	pthread_t *th=malloc(sizeof(pthread_t)*row);
	data *args=malloc(sizeof(data)*row);
	int *sum=malloc(sizeof(int));
	*sum=0;
	int **matrix=malloc(row*sizeof(int*));
	for(int i=0;i<row;i++)
		matrix[i]=malloc(col*sizeof(int));
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
			fscanf(file,"%d",&matrix[i][j]);
	printf("Matrix read\n");
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
			printf("%d\n",matrix[i][j]);
	for(int i=0;i<row;i++){
		args[i].matrix=matrix;
		args[i].id=i;
		args[i].sum=sum;
		args[i].col=col;
		args[i].mtx=mtx;
		pthread_create(&th[i],NULL,f,&args[i]);
	}
	for(int i=0;i<row;i++)
		pthread_join(th[i],NULL);
	printf("%d\n",*sum);
	pthread_mutex_destroy(mtx);
	free(mtx);
	free(th);
	free(sum);
	free(args);
	for(int i=0;i<row;i++)
		free(matrix[i]);
	free(matrix);
	return 0;
}
