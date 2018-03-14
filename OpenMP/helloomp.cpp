

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <ctime>
#include <omp.h>
#include "sha512.hpp"

#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

using namespace std;

string string_for_index(size_t index)
{
    
    return string("|") + to_string(index) + string("|");
}

int main(int argc, char *argv[])
{

    const size_t SIZE = 1000000;
    const size_t section_count = 4;
    const size_t values_per_section = SIZE / section_count;

    vector<string> hashes;
    hashes.reserve(SIZE);
    
    auto begin = Clock::now();

    if (argc == 2 && strcmp(argv[1], "-p") == 0)
    {
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
    } else 
    {
        for (size_t i = 0; i < section_count; i++)
        {
            for (size_t index = i * values_per_section; index < (i + 1) * values_per_section; index++)
                hashes[index] = sha512(string_for_index(index));
        }
    }

    

    auto end = Clock::now();

    // for (size_t i = 0; i < SIZE ; i ++)
    //     cout << hashes[i] << endl;

    cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << endl;

    return EXIT_SUCCESS;
}