
#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>

#ifdef __cpluscplus
extern "C" {
#endif

char *readFile(const char *path)
{
    FILE *file = fopen(path, "r");
    assert(file != NULL);

    fseek(file, 0, SEEK_END);

    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *str = (char *)malloc(size + 1);

    assert(fread(str, 1, size, file) == size);
    
    str[size] = 0;

    return str;
}
    
    
#ifdef __cpluscplus
}
#endif /* __cplusplus */
#endif /* __IO_H__ */
