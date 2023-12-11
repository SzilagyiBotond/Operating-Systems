#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc,char* argv[])
{
	int a2b[2],b2c[2],c2a[2];
	int n;
	pipe(a2b);
	pipe(b2c);
	pipe(c2a);
	if(fork()==0)
	{
		close(a2b[0]);
		close(b2c[1]);close(b2c[0]);
		close(c2a[1]);
		n=random() % (1000-100)+100;
		if(write(a2b[1],&n,sizeof(int))<0);
		printf("Process A writes to B %d\n",n);
		while(1)
		{
			if(read(c2a[0],&n,sizeof(int))<0)
			{
				perror("Cannot read");
				break;
			}
			printf("PRocess A reads from C %d\n",n);
			if(n<10)
			{
				break;
			}
			n++;
			write(a2b[1],&n,sizeof(int));
			printf("Process A writes to B %d\n",n);
		}
		close(a2b[1]);
		close(c2a[0]);
		exit(0);
	}
	if(fork()==0)
	{
		close(c2a[1]);
		close(c2a[0]);
		close(a2b[1]);
		close(b2c[0]);
		while(1)
		{
			if(read(a2b[0],&n,sizeof(int))<0)
			{
				perror("Cannot read");
				break;
			}
			printf("Process B reads from A %d\n",n);
			if(n<10)
			{
				break;
			}
			n=n*2;
			write(b2c[1],&n,sizeof(int));
			printf("Process B writes to C %d\n",n);
		}
		close(b2c[1]);
		close(a2b[0]);
		exit(0);
	}
	if(fork()==0)
	{
		close(a2b[1]);
		close(a2b[0]);
		close(b2c[1]);
		close(c2a[0]);
		while(1)
		{
			if(read(b2c[0],&n,sizeof(int))<0)
			{
				perror("Cannot read");
				break;
			}
			printf("Process C reads from B %d\n",n);
			if(n<10){
				break;
			}
			n=n/3;
			write(c2a[1],&n,sizeof(int));
			printf("PRocess C sends to A %d\n",n);
		}
		close(c2a[1]);
		close(b2c[0]);
		exit(0);
	}
///	wait(0);wait(0);wait(0);
	close(a2b[0]);
	close(a2b[1]);
	close(c2a[0]);
	close(c2a[1]);
	close(b2c[0]);
	close(b2c[1]);
	wait(0);
	wait(0);
	wait(0);
	return 0;
}
