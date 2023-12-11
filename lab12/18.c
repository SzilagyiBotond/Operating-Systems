#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
pthread_mutex_t *mtx;
char *string;
int id;

}data;
