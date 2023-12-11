#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char* argv[]){
int a2b=open("./a2b",O_RDONLY);
while(1){
int len;
read(a2b,&len,sizeof(int));
if(len==-1)
break;
char* buf=malloc((len+1)*sizeof(char));
read(a2b,buf,(len+1)*sizeof(char));
buf[len]=0;
printf("%s",buf);
free(buf);
fflush(stdout);
}
close(a2b);
return 0;
}
