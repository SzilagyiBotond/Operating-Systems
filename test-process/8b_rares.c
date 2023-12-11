#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc,char* argv[]){
	int a2b=open("./a2b",O_RDONLY);
	int b2a=open("./b2a",O_WRONLY);
	int len_arg;	
	read(a2b,&len_arg,sizeof(int));
	for(int i=0;i<len_arg;i++)
	{
		int len;
		read(a2b,&len,sizeof(int));
		char* buf=malloc((len+1)*sizeof(char));		

		read(a2b,buf,len*sizeof(char));
		for(int j=0;j<len;j++){
			if(buf[j]>='a' && buf[j]<='z'){
				buf[j]+='A'-'a';}
		}
		write(b2a,buf,len*sizeof(char));
		free(buf);
	}
close(a2b);
close(b2a);
return 0;
}
