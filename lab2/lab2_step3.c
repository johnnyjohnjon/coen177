/* C program to demonstrate the use of fork()*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

// main function with command line arguments
int main(int argc, char *argv[])
{
    pid_t pid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\n Before forking.\n");
    pid = fork();
    if (argc != 2)
    {
        printf("Usage: %s <delay> \n", argv[0]);
        exit(0);
    }
    if (pid < 0)
    {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }
    if (pid)
    {
        // parent process
        for (i = 0; i < 10; i++)
        {
            printf("\t \t \t I am the parent Process displaying iteration %d \n", i);
            usleep(n);
        }
    }
    else
    {
        // child process
        for (i = 0; i < 10; i++)
        {
            printf("I am the child process displaying iteration %d\n", i);
            usleep(n);
        }
    }
    return 0;
}
