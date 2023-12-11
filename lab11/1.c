#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
pthread_mutex_t mtx;
int n;
void *f(void* a){
	int done=0;
	while(1){
		pthread_mutex_lock(&mtx);
		if(abs(n)>500)
			done=1;
		else{	
		int i=random()%1001-500;
		n+=i;
		printf("%d\n",n);
}
		pthread_mutex_unlock(&mtx);
		if(done==1)
			break;
	}
	return NULL;
}
int main(int argc, char* argv[]){
	srandom(getpid());
	n=0;
	pthread_mutex_init(&mtx,NULL);
	pthread_t t1,t2,t3;
	pthread_create(&t1,NULL,f,NULL);
	pthread_create(&t2,NULL,f,NULL);
	pthread_create(&t3,NULL,f,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	pthread_mutex_destroy(&mtx);
	return 0;
}
