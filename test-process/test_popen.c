#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(){
FILE* f;
f=popen("less","w");
fprintf(f,"hey\n");
fprintf(f,"ayo\n");
pclose(f);
return 0;
}
