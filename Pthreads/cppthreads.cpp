/* Les threads POSIX, souvent appelés pthreads, 
     sont un sous-standard de la norme POSIX 
         décrivant une interface de programmation
             permettant de gérer des threads. */

// CPP Program to find sum of array
#include <iostream>
#include <thread>
#include "chrono.h"


#define NUM_THREADS 4

using namespace std;

static inline void usage()
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

void compute_on_thread(llu_t res[], unsigned long offset, unsigned long size)
{
    for (unsigned long index = offset; index < offset + size; index++)
        res[index] = sum_for_index(index);
}

llu_t compute_concurrently(unsigned long size)
{
    thread threads[NUM_THREADS];
    llu_t res[size];
    timeinterval_t begin = now();
    
    for (unsigned short index = 0; index < NUM_THREADS; index++)
    {
        threads[index] = thread([index, &res, size] () {
            unsigned long block = size / NUM_THREADS;
            unsigned long offset = index * block;
            for (unsigned long index = offset; index < offset + block; index++)
            res[index] = sum_for_index(index);
        });
    }
        
    for (unsigned short index = 0; index < NUM_THREADS; index++)
        threads[index].join();

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