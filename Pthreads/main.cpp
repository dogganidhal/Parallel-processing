/* Les threads POSIX, souvent appelés pthreads, 
     sont un sous-standard de la norme POSIX 
         décrivant une interface de programmation
             permettant de gérer des threads. */

// CPP Program to find sum of array
#include <iostream>
#include <pthread.h>
 
// size of array
#define MAX 16
 
// maximum number of threads
#define MAX_THREAD 4
using namespace std;
 
int a[] = { 1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220 };
int sum[4] = { 0 };
int part = 0;
 
void* sum_array(void* arg)
{
 
    // Each thread computes sum of 1/4th of array
    int thread_part = part++;
 
    for (int i = thread_part * (MAX / 4); i < (thread_part + 1) * (MAX / 4); i++)
        sum[thread_part] += i;
}
 
int main (int argc, char *argv[])
{
    srand((unsigned)time(NULL));
    struct timespec stop, start;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start); 
    if(argc != 3)
        usage();
    else if(strcmp(argv[1], "-s") == 0)
    {
        printf("Sequential way... \n");
        int size = atoi(argv[2]);
        sum_array(&size);
    }
    else if(strcmp(argv[1], "-p") == 0)
    {
        printf("Parallel way... \n");
 
        pthread_t threads[MAX_THREAD];
 
        // Creating 4 threads
        for (int i = 0; i < MAX_THREAD; i++)
            pthread_create(&threads[i], NULL, sum_array, (void*)NULL);
 
        // joining 4 threads i.e. waiting for all 4 threads to complete
        for (int i = 0; i < MAX_THREAD; i++)
            pthread_join(threads[i], NULL);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
    printf("Time : %lu ms \n", (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_nsec - start.tv_nsec) / 1000000);
    return EXIT_SUCCESS;
}