#include <stdio.h>
#include <pthread.h>
#define SIZE 256
#define NUM_THREADS 4
#define CHUNK SIZE / NUM_THREADS

int id [NUM_THREADS];
double sum, a[SIZE], b[SIZE];
pthread_t tid [NUM_THREADS];
pthread_mutex_t mutex_sum;

/* void* dot (void* id ) 
{
    size_t i;
    int my_first = *(int*) id * CHUNK;
    int my_last = (*(int*) id + 1) * CHUNK;
    double sum_local = 0.;
    // Computation
    for (i = my_first; i<my_last; i ++)
        sum_local = sum_local + a[i] * b[i];

    pthread_mutex_lock(&mutex_sum);
    sum = sum + sum_local;
    pthread_mutex_unlock(&mutex_sum);
    return NULL;
} */

void* sumForIndex(size_t index)
{
    long long sum = 0;
    size_t i;
    for (i = 0; i < index; i++)
        sum += i;

    pthread_mutex_lock(&mutex_sum);
    sum = sum + sum_local;
    pthread_mutex_unlock(&mutex_sum);
    return NULL;
}

int main()
{
    size_t i;
    // Initialization
    sum = 0.;
    for(i = 0; i < SIZE ; i ++)
    {
        a[i] = i * 0.5;
        b[i] = i * 2.0;
    }
    pthread_mutex_init (& mutex_sum , NULL);
    for(i = 0; i < NUM_THREADS; i++)
    {
        id [i] = i;
        pthread_create (&tid[i], NULL, sumForIndex, (void*)& id[i]);
    }
    for(i = 0; i < NUM_THREADS; i++)
        pthread_join(tid[i], NULL);
    
    pthread_mutex_destroy(&mutex_sum);
    printf("sum = %g \n", sum);
    return 0;
}