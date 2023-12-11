#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc,char* argv[]){
	int n;
	int p2c[2];
	if(pipe(p2c)<0){
		perror("Cannot open pipe");
		exit(1);
	};
	printf("What is n: ");
	scanf("%d",&n);
	printf("Read n\n");
	char filename[20];
	printf("What is the filename: ");
	scanf("%s",filename);	
	FILE* f=fopen(filename,"r");
	if(fork()==0){
		close(p2c[0]);
		int** a;
		int** b;
		int** result;
		a=(int**)malloc(n*sizeof(int*));
		b=(int**)malloc(n*sizeof(int*));
		result=(int**)malloc(n*sizeof(int*));
		for(int i=0;i<n;i++)
		{
			a[i]=(int*)malloc(n*sizeof(int));
			b[i]=(int*)malloc(n*sizeof(int));
			result[i]=(int*)malloc(n*sizeof(int));
		}
		printf("Done allocating in child\n");
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				fscanf(f,"%d",&a[i][j]);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				fscanf(f,"%d",&b[i][j]);
		printf("Done reading from file\n");
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++){
				result[i][j]=0;
				for(int k=0;k<n;k++){
					result[i][j]+=a[i][k]*b[k][j];
				}
			}
		}
		printf("Done multiplying\n");
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				write(p2c[1],&result[i][j],sizeof(int));
		fclose(f);
		for(int i=0;i<n;i++){
			free(a[i]);
			free(b[i]);
			free(result[i]);
		}
		close(p2c[1]);
		free(result);
		free(a);
		free(b);
		exit(0);
	}
	fclose(f);
	close(p2c[1]);
	int** res;
	res=malloc(n*sizeof(int*));
	for(int i=0;i<n;i++)
		res[i]=malloc(n*sizeof(int));
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			read(p2c[0],&res[i][j],sizeof(int));
			printf("%d ",res[i][j]);
		}
		printf("\n");
	}
	for(int i=0;i<n;i++)
		free(res[i]);
	free(res);
	close(p2c[0]);
	wait(0);
	return 0;
}
