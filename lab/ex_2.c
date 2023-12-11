#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
int **m,rows,cols;
FILE *f=fopen("ini","r");
if(NULL==f)
{
	perror("Error on open file");
	exit(1);
}
fscanf(f,"%d%d",&rows,&cols);
m=(int**)malloc(rows*sizeof(int*));
for(int i=0;i<rows;i++)
{	
	m[i]=(int*)malloc(cols*sizeof(int));
}
for(int i=0; i<rows;i++)
	for(int j=0;j<cols;j++){
	fscanf(f,"%d",&m[i][j]);
}
fclose(f);
for(int i=0;i<rows;i++)
{
	for(int j=0;j<cols;j++)
        	printf("%d ",m[i][j]);
	printf("\n");
}
for(int i=0; i<rows;i++)
	free(m[i]);
free(m);
return 0;	
}
