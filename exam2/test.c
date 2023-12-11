#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char*argv[]){
char* s[3]={"A","B","c"};
for(int i=0;i<3;i++)
if(fork()!=0)
execl("/bin/echo","/bin/echo",s[i],NULL);
}
