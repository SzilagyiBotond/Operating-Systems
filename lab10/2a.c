#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc,char* argv[])
{
	if(mkfifo("./fifo1",0600)<0)
	{
		perror("Error creating fifo1");
		exit(1);
	}
	if(mkfifo("./fifo2",0600)<0)
	{
		perror("Error creating fifo2");
		exit(1);
	}
	int fd_write=open("./fifo1",O_WRONLY);
	if(fd_write==-1)
	{
		perror("Error opening fifo1 in A");
		exit(1);
	}
	int fd_read=open("./fifo2",O_RDONLY);
	if(fd_read==-1)
	{
		close(fd_write);
		perror("Error opening fifo2");
		exit(1);
	}
	srandom(getpid());
	int n=random() % 1001;
	printf("The target number is %d\n",n);
	int count=0;
	int not_guess=1;
	while(not_guess)
	{
		int guess;
		if(0>read(fd_read,&guess,sizeof(int))){
			perror("Cannot read from fifo1 in A");
			exit(1);	
		}
		if(guess<n)
		{
			not_guess=-1;
			count++;
		}
		if(guess>n)
		{
			not_guess=1;
			count++;
		}
		if(guess==n)
			not_guess=0;
		if(0<write(fd_write,&not_guess,sizeof(int)))
		{
			perror("Cannot wrtie to fifo2 on A");
			break;
		}
	}
	close(fd_write);
	close(fd_read);
	printf("B guessed the number in %d tries\n",count);
//	if(0>unlink("./fifo1"))
//{
//perror("Cannot delete fifo1");
//}
//if(0>unlink("./fifo2"))
//{
//perror("Cannot delete fifo2");
//}
return 0;
}
