#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#define workers 4

void * doWork(void * param);

void * test(void* param)
{
	int id = (int)(intptr_t)(param);
	printf("Worker [%d] \n",id);
	return NULL;
}

int main()
{
	pthread_t threads[workers];
	int i; 

	for(i = 0; i < workers; i ++)
	{
		pthread_create(&threads[i],NULL,test,(void *) (intptr_t)i);
	}

	for(i = 0; i < workers; i ++)
	{
		pthread_join(threads[i],NULL);
	}

	return 0;
}

void * doWork(void * param)
{
	int id = (int)(intptr_t)(param);
	printf("Worker [%d] \n",id);
	return NULL;
}