#ifndef __CHRONO_H__
#define __CHRONO_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct timeval timeinterval_t;

typedef enum { SECONDS, MILLISECONDS, MICROSECONDS } timeunit;

timeinterval_t now()
{
    timeinterval_t tv;
    gettimeofday(&tv, NULL);
    return tv;
}

long long time_elapsed(timeinterval_t begin, timeinterval_t end, timeunit unit)
{
    switch (unit)
    {
        case SECONDS:
            return (double)end.tv_sec + (double)end.tv_usec / (double)1000000 - (double)begin.tv_sec - (double)begin.tv_usec / (double)1000000;
        case MILLISECONDS:
            return (double)end.tv_sec * 1000 + (double)end.tv_usec / (double)1000 - (double)begin.tv_sec * 1000 - (double)begin.tv_usec / (double)1000;
        case MICROSECONDS:
            return (double)end.tv_sec * 1000000 + (double)end.tv_usec - (double)begin.tv_sec * 1000000 - (double)begin.tv_usec;
    }
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __CHRONO_H__ */