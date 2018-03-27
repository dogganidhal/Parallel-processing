

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <omp.h>
#include "sha512.hpp"

using namespace std;

string randomString(unsigned short length)
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    char randomString[length];
    for (size_t index = 0; index < length; index++)
        randomString[index] = alphanum[rand() % (sizeof(alphanum) - 1)];
    return string(randomString);
}

int main(int argc, char *argv[])
{

    if (argc != 3) 
    {
        cout << "Usage : ./helloworld [-ps] number_of_iterations" << endl;
        exit(EXIT_FAILURE);
    }

    const size_t SIZE = atoi(argv[2]);
    vector<string> hashes;
    hashes.reserve(SIZE);
    
    auto begin = chrono::high_resolution_clock::now();

    if (strcmp(argv[1], "-p") == 0)
    {
        /* PARALLEL */
        #pragma omp parallel for
        for (size_t index = 0; index < SIZE; index++)
            hashes[index] = sha512(randomString(16));
    } else if (strcmp(argv[1], "-s") == 0)
    {
        /* SEQUENTIAL */
        for (size_t index = 0; index < SIZE; index++)
            hashes[index] = sha512(randomString(16));
    } else 
    {
        cout << "Usage: ./helloworld [-ps] number_of_iterations" << endl;
        exit(EXIT_FAILURE);
    }

    auto end = chrono::high_resolution_clock::now();

    cout << "Time elapsed: " << chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << endl;

    return EXIT_SUCCESS;
}
