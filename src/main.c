#define _POSIX_C_SOURCE 199309L

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define NUM_THREADS     4

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);
   return NULL;
}

void *runfor(void *threadid)
{
   struct timespec start, finish;
   double elapsed;

   clock_gettime(CLOCK_MONOTONIC, &start);

   while (elapsed < 10)
   {
      //printf("%lf\n", elapsed);
      clock_gettime(CLOCK_MONOTONIC, &finish);

      elapsed = (finish.tv_sec - start.tv_sec);
      elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
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
   for(int i = 0; i < threadCount; i ++)
   {
      pthread_join(threads[i],NULL);
   }

   /* Last thing that main() should do */
   pthread_exit(NULL);
}
