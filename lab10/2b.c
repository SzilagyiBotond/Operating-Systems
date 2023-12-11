#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc,char* argv[])
{
	int fd_read=open("./fifo1",O_RDONLY);
	if(fd_read==-1)
	{
		perror("Cannot open fifo1 in B");
		exit(1);
	}
	int fd_write=open("./fifo2",O_WRONLY);
	if(fd_write==-1)
	{
		close(fd_read);
		perror("Cannot open fifo2 in B");
		exit(1);
	}
	int min=0;
	int max=1001;
	int not_guessed=1;
	srandom(getpid());
	while(not_guessed)
	{
		int guess=random() % max;
		if(write(fd_write,&guess,sizeof(int))<0)
		{
			perror("Error on write to A");
			break;
		}
		if(read(fd_read,&not_guessed,sizeof(int))<0)
		{
			perror("Error on read from A");
			break;
		}
		if(not_guessed==-1)
		{
		}
		if(not_guessed==1)
		{

		}
		sleep(1);
	}
	close(fd_read);
	close(fd_write);

	return 0;
}
