/* Les threads POSIX, souvent appelés pthreads, 
     sont un sous-standard de la norme POSIX 
         décrivant une interface de programmation
             permettant de gérer des threads. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdnoreturn.h>
#include "chrono.h"

#define NUM_THREADS 4

noreturn static inline void usage()
{
    fprintf(stderr, "usage: ./main [-s|-p] \n"); 
    exit(1);
}

static inline llu_t sum_for_index(unsigned long index)
{
    llu_t sum = 0;
    for (unsigned long i = 0; i < index; i++)
        sum += i;
    return sum;
}

llu_t compute_sequentially(unsigned long size)
{
    llu_t res[size];
    timeinterval_t begin = now();
    for (unsigned long index = 0; index < size; index++)
        res[index] = sum_for_index(index);
    timeinterval_t end = now();
    return time_elapsed(begin, end, MILLISECONDS);
}

struct index_size
{
    llu_t *__ptr;
    unsigned long size;
};

void *compute_on_thread(void *__ptr)
{
    struct index_size arg = *((struct index_size *)__ptr);
    for (unsigned long index = 0; index < arg.size; index++)
        *(arg.__ptr + index) = sum_for_index(index);
    return NULL;
}

llu_t compute_concurrently(unsigned long size)
{
    pthread_t threads[NUM_THREADS];
    llu_t res[size];
    timeinterval_t begin = now();
    for (unsigned short index = 0; index < NUM_THREADS; index++)
    {
        struct index_size arg = {res + (size / NUM_THREADS) * index, size / NUM_THREADS};
        if (pthread_create(&threads[index], NULL, compute_on_thread, 
                           (void *)(&arg)) != 0)
            perror("pthread_create");
    }
    for (unsigned short index = 0; index < NUM_THREADS; index++)
        pthread_join(threads[index], NULL);

    timeinterval_t end = now();
    return time_elapsed(begin, end, MILLISECONDS);
}

int main (int argc, char *argv[])
{
    
    if (argc != 3) usage();
    llu_t t = 0;
    if (strcmp(argv[1], "-s") == 0)
        t = compute_sequentially(atoi(argv[2]));
    else if (strcmp(argv[1], "-p") == 0)
        t = compute_concurrently(atoi(argv[2]));
    else 
        usage();

    printf("time elapsed: %llu ms\n", t);

    return EXIT_SUCCESS;
}