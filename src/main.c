#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define NUM_THREADS     7

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);
   return NULL;
}

void *runfor(void *threadid)
{
   clock_t start = clock(), diff;
   int msec = 0;
   while (msec/1000 < 50)
   {
      diff = clock() - start;
      msec = diff * 1000 / CLOCKS_PER_SEC;
   }
   return NULL;
}

int main (int argc, char *argv[])
{
   int threadCount = sysconf(_SC_NPROCESSORS_ONLN);
   pthread_t threads[threadCount];
   int rc;
   long t;
   
   printf("Available threads: %ld\n", sysconf(_SC_NPROCESSORS_ONLN));
   for(t=0; t<threadCount; t++){
      printf("In main: creating thread %ld\n", t);
      rc = pthread_create(&threads[t], NULL, runfor, (void *)t);
      if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }

   /* Last thing that main() should do */
   pthread_exit(NULL);
}
