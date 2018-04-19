

#import <Foundation/Foundation.h>
#import <string.h>
#import "chrono.h"

size_t sum_for_index(unsigned index)
{
    size_t sum = 0;
    for (unsigned i = 0; i < index; i++)
        sum += i;
    return sum;
}

void compute_sequentially(size_t iterations)
{
    size_t sums[iterations];
    for (int i = 0; i < iterations; i++) {
        sums[i] = sum_for_index(i);
    }
}

void compute_concurrently(size_t iterations)
{
    __block size_t *sums = malloc(iterations * sizeof(size_t));
    dispatch_queue_t queue = dispatch_queue_create("queue", DISPATCH_QUEUE_CONCURRENT);
    dispatch_apply(iterations, queue, ^(size_t index) {
        sums[index] = sum_for_index((unsigned)index);
    });
    free(sums);
}


int main(int argc, const char * argv[])
{

    if (argc != 3)
    {
        NSLog(@"Usage: gcd -[s|p] ITERATIONS");
        return 1;
    }
    
    timeinterval_t begin = now();

    if (strcmp(argv[1], "-s") == 0)
        compute_sequentially(atoi(argv[2]));
    else if (strcmp(argv[1], "-p") == 0)
        compute_concurrently(atoi(argv[2]));
    else   
    {
        NSLog(@"Usage: gcd -[s|p] ITERATIONS");
        return 1;
    }
    
    timeinterval_t end = now();
    
    NSLog(@"time elapsed: %llu ms", time_elapsed(begin, end, MILLISECONDS));
    
    return 0;
}