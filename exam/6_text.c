#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char* argv[]){
int k=fork();
if(k==0)
{printf("A\n");
exit(0);
}
else
printf("B\n");
printf("C\n");
return 0;
}
