/* Les threads POSIX, souvent appelés pthreads, 
     sont un sous-standard de la norme POSIX 
         décrivant une interface de programmation
             permettant de gérer des threads. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <pthread.h>

void usage (void)
{
    fprintf(stderr, "usage: ./main [-s|-p] \n");
    exit(1);
}

long int index_computation(int iterations) //A determiner ?
{
    long int res; int i;
    for (i = 0; i <= iterations; i++)
    {
        res += 3*i;
    }
    return res;
}

int main (int argc, char *argv[])
{
    if(argc != 2)
        usage();
    else if(strcmp(argv[1], "-s") == 0)
    {
        printf("Sequential way... \n");
        int iterations;
        printf ("Number of iterations? ");
        scanf ("%d", &iterations);
        long int res = index_computation(iterations);
        printf("%ld \n", res);
    }
    else if(strcmp(argv[1], "-p") == 0)
    {
        printf("Parallel way... \n");
    }

    return EXIT_SUCCESS;

}