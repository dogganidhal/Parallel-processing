/* Les threads POSIX, souvent appelés pthreads, 
     sont un sous-standard de la norme POSIX 
         décrivant une interface de programmation
             permettant de gérer des threads. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

void usage (void)
{
    fprintf(stderr, "usage: ./main [-s|-p] \n");
    exit(1);
}

int recherche(long int* const tab, int a, int b, int x)
{
	if (a >= b) return a;
	int m = (a + b) / 2;
	if (tab[m] < x) return recherche(tab, m + 1, b, x);
	else return recherche(tab, a, m, x);
}
void inserer(long int* const tab, int n, int pos, int x)
{
	int i;
	for (i = n; i>pos; i--) tab[i] = tab[i - 1];
	tab[pos] = x;
}

long int* custom_sort(size_t size, long int* array)
{
  long int* result = malloc(size * sizeof(long int));
  size_t i;
  for (i = 0; i<size; i++)
  {
	  int pos = recherche(result, 0, i, array[i]);
	  inserer(result, i, pos, array[i]);
  }
  return result;
}

long int random_val()
{
    return (int)rand();
}

void print_array(long int *array, int length)
{
    int i;
    for (i = 0; i < length; i++)
    printf("%ld \n", array[i]);
}

void *computation(void* arg)
{
        int i, size = *((int*) arg);
        long int array[size];
        for (i = 0; i <= size; i++)
            array[i] = random_val();
        
        long int *sorted_array = custom_sort(size, array);
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
    computation(&size);
    }
    else if(strcmp(argv[1], "-p") == 0)
    {
        printf("Parallel way... \n");
        int nb_threads = 4;

        thread_t thread[nb_threads];

        int i, size = atoi(argv[2]);
        for (i = 0; i < nb_threads; i++)
        {
            thread_t t;
            thread[i] = t;
            if(pthread_create(&t, NULL, computation, &size) == -1)
            {
	            perror("pthread_create");
	            return EXIT_FAILURE;
            }
        }
        for (i = 0; i < nb_threads; i++)
        { 
            if(pthread_join(thread[i], NULL)) 
            {
	            perror("pthread_join");
	            return EXIT_FAILURE;
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
    printf("Time : %lu ms \n", (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_nsec - start.tv_nsec) / 1000000);
    return EXIT_SUCCESS;
}

//ERROR INITIALISATION THREADS