

#include <iostream>
#include <omp.h>

using namespace std;

/**
 * Compile:
 * clang++ -Xpreprocessor -fopenmp -lomp helloomp.cpp
 */

int main(int argc, char *argv[])
{

    int nthreads, tid;

    /* Fork a team of threads giving them their own copies of variables */
    #pragma omp parallel private(nthreads, tid)
    {

        /* Obtain thread number */
        tid = omp_get_thread_num(); 
        cout << "Hello World from thread = " << tid << endl;

        /* Only master thread does this */
        if (tid == 0) 
        {
            nthreads = omp_get_num_threads();
            cout << "Number of threads = " << nthreads << endl;
        }

    }  /* All threads join master thread and disband */

    return EXIT_SUCCESS;
}