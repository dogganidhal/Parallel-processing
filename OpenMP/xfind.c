
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <sys/types.h>
#include "../helpers/chrono.h"

typedef enum { PARALLEL, SEQUENTIAL } processing_mode;

void parse_args(int argc, char *argv[], processing_mode *mode, char **file_name, int *matching_flag)
{
    *matching_flag = 0;
    for (int index = 0; index < argc; index++)
    {
        if (strcmp(argv[index], "--sequential") == 0)
            *mode = SEQUENTIAL;
        else if (strcmp(argv[index], "--parallel") == 0)
            *mode = PARALLEL;
        else if (strcmp(argv[index], "--match") == 0)
            *matching_flag = 1;
        else if (*argv[index] == '-')
        {
            fprintf(stderr, "non-reconized option %s\n", argv[index]);
            exit(EXIT_FAILURE);
        } else 
        {
            *file_name = realloc(*file_name, strlen(argv[index]) + 1);
            strcpy(*file_name, argv[index]);
        }   
    }
}

char *append_path(const char *basepath, const char *subpath)
{
    char *newpath = malloc((strlen(basepath) + strlen(subpath) + 2) * sizeof(char));
    
    strcpy(newpath, basepath);
    if (strcmp(basepath, "/") != 0)
        strcat(newpath, "/");
    strcat(newpath, subpath);
    
    return newpath;
}

void explore_directory_sequential(const char *path, const char *filename, int matching_flag)
{
    DIR *dir = opendir(path);
    if (dir == NULL) return;

    struct dirent *dirent = NULL;

    while ((dirent = readdir(dir)) != NULL)
    {
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0)
            continue;
        char *subpath = append_path(path, dirent->d_name);
        if (dirent->d_type == DT_DIR)
        {
            explore_directory_sequential(subpath, filename, matching_flag);
            free(subpath);
        } else if (!matching_flag && strstr(dirent->d_name, filename) != NULL)
            printf("%s\n", subpath);
        else if (matching_flag && strcmp(dirent->d_name, filename) == 0)
            printf("%s\n", subpath);
    }
    closedir(dir);
    free(dirent);
}

void explore_directory_parallel(const char *path, const char *filename)
{
    DIR *dir = opendir(path);
    if (dir == NULL) return;
    struct dirent **entries = NULL, *dirent = NULL;

    size_t number_of_entries = 0, number_of_paths = 0;
    char **paths = NULL;

    while ((dirent = readdir(dir)) != NULL)
    {
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0)
            continue;
        entries = realloc(entries, (++number_of_entries) * sizeof(struct dirent *));
        entries[number_of_entries - 1] = dirent;
    }

    #pragma omp parallel for
    for (size_t index = 0; index < number_of_entries; index++)
    {
        if (strcmp(entries[index]->d_name, ".") == 0 || strcmp(entries[index]->d_name, "..") == 0)
            continue;
        char *subpath = append_path(path, entries[index]->d_name);
        struct stat *filestat = malloc(sizeof(struct stat));
        stat(subpath, filestat);

        assert(filestat != NULL);

        if (S_ISDIR(filestat->st_mode))
        {
            explore_directory_parallel(subpath, filename);
            free(subpath);
        } else if (strstr(entries[index]->d_name, filename) != NULL)
        {
            paths = realloc(paths, (++number_of_paths) * sizeof(char *));
            paths[number_of_paths - 1] = subpath;
        }
    }

    closedir(dir);
    free(dirent);

    for (size_t index = 0; index < number_of_paths; index++)
        printf("%s\n", paths[index]);
    
    free(paths);
    free(entries);

}

void look_for_file(const char *filename, processing_mode mode, int matching_flag)
{
    if (mode == PARALLEL)
        explore_directory_parallel("/", filename);
    else 
        explore_directory_sequential("/", filename, matching_flag);
}

int main(int argc, char *argv[])
{

    int matching_flag = 0;
    processing_mode mode;
    char *filename = NULL;

    parse_args(argc, argv, &mode, &filename, &matching_flag);

    timeinterval_t begin = now();

    look_for_file(filename, mode, matching_flag);

    timeinterval_t end = now();

    long long elapsed = time_elapsed(begin, end, MILLISECONDS);

    printf("time: %lld ms\n", elapsed);

    return EXIT_SUCCESS;
}