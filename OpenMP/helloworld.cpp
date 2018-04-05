

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <omp.h>
#include "string.h"

using namespace std;

long long sumForIndex(size_t index)
{
    long long sum = 0;
    for (size_t i = 0; i < index; i++)
        sum += i;
    return sum;
}

int main(int argc, char *argv[])
{

    if (argc != 3) 
    {
        cout << "Usage : ./omp [-p|s] number_of_iterations" << endl;
        exit(EXIT_FAILURE);
    }

    const size_t SIZE = atoi(argv[2]);
    vector<long long> sums;
    sums.reserve(SIZE);
    
    auto begin = chrono::high_resolution_clock::now();

    if (strcmp(argv[1], "-p") == 0)
    {
        /* PARALLEL */
        #pragma omp parallel for schedule(dynamic, 2)
        for (size_t index = 0; index < SIZE; index++)
        {
            long long sum = 0;
            for (size_t i = 0; i < index; i++)
                sum += i;   
        }
    } else if (strcmp(argv[1], "-s") == 0)
    {
        /* SEQUENTIAL */
        for (size_t index = 0; index < SIZE; index++)
        {
            long long sum = 0;
            for (size_t i = 0; i < index; i++)
                sum += i;   
        }
    } else 
    {
        cout << "Usage: ./omp [-p|s] number_of_iterations" << endl;
        exit(EXIT_FAILURE);
    }

    auto end = chrono::high_resolution_clock::now();

    cout << SIZE << ", " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << endl;

    return EXIT_SUCCESS;
}
