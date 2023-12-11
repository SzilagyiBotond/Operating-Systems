#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc,char* argv[])
{
	if(mkfifo("./a2b",0600))
	{
		perror("Error on fifo");
		exit(1);
	}
	if(mkfifo("./b2a",0600))
	{
		perror("Errpr on fifo");
		exit(1);
	}
	int a2b=open("./a2b","w");
	int b2a=open("./b2a","r");
	if(0>a2b)
	{
		perror("Error");
		exit(1);
	}
	if(0>b2a)
	{
		perror("Error");
		exit(1);
	}
	srand(getpid());
	int nr=rand() % 1001;
	
	unlink("./b2a");
	unlink("./a2b");
	return 0;
}
