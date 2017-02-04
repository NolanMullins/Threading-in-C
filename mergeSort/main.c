#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

typedef struct data
{
	int id;
	int* arr;
	int size;
	int* threadsIsUse;
	int maxThreads;
} Data;

void merge(int* a, int sa, int* b, int sb, int* main)
{
	int  i=0, j=0, k=0;
	while (i < sa && j < sb)
	{
		if (a[i] < b[j])
			main[k] = a[i++];
		else
			main[k] = b[j++];
		k++;
	}
	if (i == sa)
		while (j < sb)
			main[k++] = b[j++];
	else
		while (i < sa)
			main[k++] = a[i++];
}

void cpyData(Data* data, Data* newData, int* arr, int size)
{
	newData->id = data->id;
	newData->arr = arr;
	newData->size = size;
	newData->threadsIsUse = data->threadsIsUse;
	newData->maxThreads = data->maxThreads;
}

void* mergeSort(void* param)
{
	Data* data = (Data*)param;
	if (data->size <= 1)
		return NULL;

	int* arr = data->arr;
	int size = data->size;
	
	int sa = size/2;
	int sb = size - (int)(size/2);
	int* arrA = malloc(sizeof(int)*sa);
	int* arrB = malloc(sizeof(int)*sb);
	int a;
	for (a = 0; a < sa; a++)
		arrA[a] = arr[a];
	for (int b = 0; b < sb; b++)
		arrB[b] = arr[a++];

	Data dataA, dataB;
	cpyData(data, &dataA, arrA, sa);
	cpyData(data, &dataB, arrB, sb);
	//sort
	int flag = 0;
	pthread_t thread;

	if (*(data->threadsIsUse) < (data->maxThreads-1))
	{
		*(data->threadsIsUse) += 1;
		dataA.id = *(data->threadsIsUse);
		//printf("Creating new Thread: %d\n", dataA.id);
		flag = 1;
		int sts = pthread_create(&thread, NULL, mergeSort, &dataA);
		if (sts)
		{
			printf("error creating thread, error code: %d\n", sts);
			flag = 0;
			mergeSort(&dataA);
		}
	}
	else
	{
		mergeSort(&dataA);
	}
	mergeSort(&dataB);
	//merge
	if (flag)
		 pthread_join(thread,NULL);
	merge(arrA, sa, arrB, sb, arr);
	free(arrA);
	free(arrB);
	return NULL;
}

int start (char* file)
{
	//tmp array for testing
	int tmpS = 10000000;
	int* arrtmp = malloc(sizeof(int)*tmpS);

	for (int a = 0; a<tmpS; a++)
		arrtmp[a] = rand()%(tmpS*1000) + 1;

	//threading
	int threadCount = sysconf(_SC_NPROCESSORS_ONLN);
	printf("%d threads available\nSorting\n", threadCount);
	int threadUse = 0;
	Data data;
	data.id = 0;
	data.arr = arrtmp;
	data.size = tmpS;
	data.threadsIsUse = &threadUse;
	data.maxThreads = threadCount;


	struct timespec start, finish;
	double elapsed;

	clock_gettime(CLOCK_MONOTONIC, &start);

	mergeSort(&data);

	clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("time taken: %lf\n", elapsed);

	/*for (int a = 0; a < 10; a++)
		printf("%d\n", arrtmp[a]);
	for (int a = tmpS-10; a < tmpS; a++)
		printf("%d\n", arrtmp[a]);*/

    free(arrtmp);
	return 0;
}

int main(int argc, char* argv[])
{
	//printf("inv %d\n", q1("data/q1"));
	srand(time(NULL));
	start("data/q1");
	return 0;
}