/* Les threads POSIX, souvent appelés pthreads, 
     sont un sous-standard de la norme POSIX 
         décrivant une interface de programmation
             permettant de gérer des threads. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/times.h>
//#include <pthread.h>

void usage (void)
{
    fprintf(stderr, "usage: ./main [-s|-p] \n");
    exit(1);
}

int recherche(long int* const tab, int a, int b, int x)
{
	if (a >= b) return a;
	int m = (a + b) / 2;
	if (tab[m]<x) return recherche(tab, m + 1, b, x);
	else return recherche(tab, a, m, x);
}
void inserer(long int* const tab, int n, int pos, int x)
{
	int i;
	for (i = n; i>pos; i--) tab[i] = tab[i - 1];
	tab[pos] = x;
}

long int* custom_sort(size_t size, long int* const array)
{
  long int* const result = malloc(size * sizeof *result);
  size_t i;
  for (i = 0; i<size; i++)
  {
	  int pos = recherche(result, 0, i, array[i]);
	  inserer(result, i, pos, array[i]);
  } 
  free(array);
  return result;
}

long int random_val(int max, int min)
{
    return (int)rand()/(RAND_MAX) * (max - min) + min;
}

void print_array(long int *array, int length)
{
    int i;
    for (i = 0; i < length; i++)
    printf("%ld \n", array[i]);
}

int main (int argc, char *argv[])
{
    srand((unsigned)time(NULL));
    if(argc != 3)
        usage();
    else if(strcmp(argv[1], "-s") == 0)
    {
        printf("Sequential way... \n");
        int i, size = atoi(argv[2]);
        long int array[size];
        for (i = 0; i <= size; i++)
            array[i] = random_val(0, 100000);
        print_array(array, size);
    }
    else if(strcmp(argv[1], "-p") == 0)
    {
        printf("Parallel way... \n");
    }

    return EXIT_SUCCESS;

}