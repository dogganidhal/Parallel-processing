

#include <iostream>
#include <vector>
#include <string>
#include <omp.h>
#include "sha512.hpp"

using namespace std;

string string_for_index(size_t index)
{
    
    return string("|") + to_string(index) + string("|");
}

int main(int argc, char *argv[])
{

    const size_t SIZE = 1000000;
    const size_t section_count = 5;
    const size_t values_per_section = SIZE / section_count;

    string hashes[SIZE];
    
    #pragma omp parallel
    {
        #pragma omp sections
        {
            for (size_t i = 0; i < section_count; i++)
            {
                #pragma omp section
                for (size_t index = i * values_per_section; index < (i + 1) * values_per_section; index++)
                    hashes[index] = sha512(string_for_index(index));
            }
        }
    }
    for (size_t i = 0; i < SIZE ; i ++)
        cout << hashes[i] << endl;

    return EXIT_SUCCESS;
}