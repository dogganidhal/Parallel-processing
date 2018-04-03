

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <assert.h>

#define STEP 256

void execute_iterations(const char *executable, unsigned long iterations)
{
    char csvname[20];
    sprintf(csvname, "%s.csv", executable);
    int csvfd = open(csvname, O_CREAT | O_RDWR, 0666);
    
    int pip[2];
    if (pipe(pip) == -1)
        perror("pipe");

    pid_t pid = fork();

    switch (pid)
    {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
        case 0: /* child process, do the writing */
            if (close(pip[0]) == -1) /* close the input */
                perror("close");
            if (dup2(pip[1], STDOUT_FILENO) == -1)
                perror("dup2");

            if (close(pip[1]) == -1) /* close the output */
                perror("close");
            unsigned long index;
            for (index = STEP; index <= iterations; index += STEP)
            {
                char command[1024];
                sprintf(command, "%s -s %lu", executable, index);
                system(command);
            }
            exit(EXIT_SUCCESS);
        default: /* parent process, do the reading */
            if (close(pip[1]) == -1) /* close the output */
                perror("close");

            char data[1024];
            size_t size;
            
            while ((size = (read(pip[0], data, 1024))) > 0)
            {
                if (write(csvfd, data, size) < 0)
                    perror("write");
            }
            
            close(pip[0]);
            break;
    }
    if (wait(NULL) == -1)
        perror("wait");
    close(csvfd);
}

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./csvgen executable max_iterations");
        exit(EXIT_FAILURE);
    }

    execute_iterations(argv[1], atoi(argv[2]));

    return EXIT_SUCCESS;
}