
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/dir.h>

typedef enum { PARALLEL, SEQUENTIAL } processing_mode;

void parse_args(int argc, char *argv[], processing_mode *mode, char **file_name)
{
    for (int index = 0; index < argc; index++)
    {
        if (strcmp(argv[index], "-s") == 0 || strcmp(argv[index], "--sequential") == 0)
            *mode = SEQUENTIAL;
        else if (strcmp(argv[index], "-p") == 0 || strcmp(argv[index], "--parallel") == 0)
            *mode = PARALLEL;
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
    strcat(newpath, "/");
    strcat(newpath, subpath);
    
    return newpath;
}

void explore_directory_sequential(const char *path, const char *filename)
{
    DIR *dir = opendir(path);
    if (dir == NULL) return;
    
    struct dirent *dirent = NULL;

    while ((dirent = readdir(dir)) != NULL)
    {
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0)
            continue;
        char *subpath = append_path(path, dirent->d_name);
        struct stat *filestat = malloc(sizeof(struct stat));
        stat(subpath, filestat);

        assert(filestat != NULL);

        if (S_ISDIR(filestat->st_mode))
        {
            explore_directory_sequential(subpath, filename);
            free(subpath);
        } else if (strcmp(dirent->d_name, filename) == 0)
        {
            printf("%s\n", subpath);
        }
    }

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
        } else if (strcmp(entries[index]->d_name, filename) == 0)
        {
            paths = realloc(paths, (++number_of_paths) * sizeof(char *));
            paths[number_of_paths - 1] = subpath;
        }
    }

    for (size_t index = 0; index < number_of_paths; index++)
        printf("%s\n", paths[index]);

}

void look_for_file(const char *filename, processing_mode mode)
{
    if (mode == PARALLEL)
        explore_directory_parallel("/", filename);
    else 
        explore_directory_sequential("/", filename);
}

int main(int argc, char *argv[])
{

    processing_mode mode;
    char *filename = NULL;

    parse_args(argc, argv, &mode, &filename);

    look_for_file(filename, mode);

    return EXIT_SUCCESS;
}