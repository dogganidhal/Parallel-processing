

#include <iostream>
#include <vector>
#include <string>
#include <omp.h>
#include "sha512.hpp"

#include <chrono>


using namespace std;

string string_for_index(size_t index)
{
    
    return string("|") + to_string(index) + string("|");
}

int main(int argc, char *argv[])
{

    if (argc < 2) 
    {
        cout << "Usage : ./omptest [-p] number_of_iterations" << endl;
        exit(EXIT_FAILURE);   
    }

    const size_t SIZE = argc == 2 ? atoi(argv[1]) : atoi(argv[2]);
    const size_t values_per_section = SIZE / 4;

    vector<string> hashes;
    hashes.reserve(SIZE);
    
    auto begin = chrono::high_resolution_clock::now();

    if (argc == 3)
    {
        /* PARALLEL */
        #pragma omp parallel for
        for (size_t index = 0; index < SIZE; index++)
            hashes[index] = sha512(string_for_index(index));
        /* ANOTHER WAY TO DO IT
        #pragma omp parallel
        {
            #pragma omp sections
            {
                #pragma omp section
                for (size_t index = 0; index < values_per_section; index++)
                {
                    hashes[index] = sha512(string_for_index(index));
                }
                #pragma omp section
                for (size_t index = values_per_section; index < 2 * values_per_section; index++)
                {
                    hashes[index] = sha512(string_for_index(index));
                }
                #pragma omp section
                for (size_t index = 2 * values_per_section; index < 3 * values_per_section; index++)
                {
                    hashes[index] = sha512(string_for_index(index));
                }
                #pragma omp section
                for (size_t index = 3 * values_per_section; index < 4 * values_per_section; index++)
                {
                    hashes[index] = sha512(string_for_index(index));
                }
            }
        }
        */
    } else 
    {
        /* SEQUENTIAL */
        for (size_t index = 0; index < SIZE; index++)
            hashes[index] = sha512(string_for_index(index));
    }

    

    auto end = chrono::high_resolution_clock::now();

    cout << "Time elapsed: " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;

    return EXIT_SUCCESS;
}