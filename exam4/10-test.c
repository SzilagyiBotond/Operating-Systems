#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
int p[2];
pipe(p);
int n;
char buff[10];
n=read(p[0],buff,10);
printf("%d",n); 
}
