#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int agrc,char* argv[])
{
	char* filename=(char*)malloc(10*sizeof(char));
	scanf("%s",filename);
	FILE *f=fopen(filename,"r");
	int n;
	fscanf(f,"%d",&n);
	int pc[2];
	pipe(pc);
	int** matrixa;
	matrixa=(int**)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++)
		matrixa[i]=(int*)malloc(n*sizeof(int));
	int** matrixb;
	matrixb=(int**)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++)
		matrixb[i]=(int*)malloc(n*sizeof(int));
	int** matrixc;
	matrixc=(int**)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++)
		matrixc[i]=(int*)malloc(n*sizeof(int));
	if(fork()==0)
	{
		close(pc[0]);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				fscanf(f,"%d",&matrixa[i][j]);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				fscanf(f,"%d",&matrixb[i][j]);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++){
				matrixc[i][j]=matrixa[i][j]+matrixb[i][j];
				write(pc[1],&matrixc[i][j],sizeof(int));
			}
		close(pc[1]);
		free(filename);
		for(int i=0;i<n;i++)
			free(matrixa[i]);
		free(matrixa);
		for(int i=0;i<n;i++)
			free(matrixb[i]);
		free(matrixb);
		for(int i=0;i<n;i++)
			free(matrixc[i]);
		free(matrixc);
		fclose(f);
		exit(0);
	}
	close(pc[1]);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			read(pc[0],&matrixc[i][j],sizeof(int));
	close(pc[0]);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			printf("%d ",matrixc[i][j]);

		printf("\n");
	}
	free(filename);
	for(int i=0;i<n;i++)
		free(matrixa[i]);
	free(matrixa);
	for(int i=0;i<n;i++)
		free(matrixb[i]);
	free(matrixb);
	for(int i=0;i<n;i++)
		free(matrixc[i]);
	free(matrixc);
	wait(0);
	fclose(f);
	return 0;
}
