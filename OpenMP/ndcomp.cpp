

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;

struct ndcomp_args {
    bool pflag;
    vector<char *> *input;
};

ndcomp_args parse_args(int argc, char *argv[])
{
    ndcomp_args args;
    args.input = new vector<char *>();
    args.pflag = false;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-p") == 0) args.pflag = true;
        else args.input->push_back(argv[i]);
    }
    return args;
}

void compress_input(ndcomp_args args)
{
    for (int i = 0; i < args.input->size(); i++)
    {
        ifstream file(args.input->at(i));
        file.seekg(0, file.end);
        long long size = file.tellg();
        file.seekg(0, file.beg);
        for (long long j = 0; j < size; j++)
        {
            char c;
            file.read(&c, 1);
            printf("%X", c);
        }
        file.close();
    }
}

int main(int argc, char *argv[])
{

    try 
    {

        ndcomp_args args = parse_args(argc, argv);

        auto begin = chrono::high_resolution_clock::now();

        compress_input(args);

        auto end = chrono::high_resolution_clock::now();

    } catch (exception e) 
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}