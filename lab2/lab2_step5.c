// Name: Han Duan
// Date: 1/26/2023
// Title: Lab2 P5
// Description: Multi Processing
#include <stdio.h>     /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* fork */
#include <stdlib.h>    /* atoi */
#include <errno.h>     /* errno */
/* main function*/
int main(int argc, char *argv[])
{
    pid_t pid, pid2;
    int i, n = atoi(argv[1]), m = atoi(argv[2]), o = atoi(argv[3]), p = atoi(argv[4]); // n is a delay in microseconds inserted in parent and child iterations
    printf("\n Before forking.\n");
    pid = fork();
    pid2 = fork();

    if (pid < 0)
    {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if (pid)
    {
        if (pid2)
        {
            // Parent of both: pid is > 0 and pid2 > 0
            for (i = 0; i < 10; i++)
            {
                printf("\t \t \t I am the parent of process one and two %d \n", i);
                usleep(n);
            }
        }
        // Parent of first and child of second: pid is > 0 and pid2 == 0
        else
        {
            for (i = 0; i < 10; i++)
            {
                printf("\t \t  I am the parent of the first process and child of the second %d \n", i);
                usleep(m);
            }
        }
    }
    else
    {
        if (pid2)
        {
            // Child of first process and parent of second: pid = 0 and pid2 > 0
            for (i = 0; i < 10; i++)
            {
                printf("\t I am the child process of first and parent of second %d\n", i);
                usleep(o);
            }
        }
        // Child of first and second process: pid = 0 and pid2 = 0
        else
        {
            for (i = 0; i < 10; i++)
            {
                printf("I am the child process of first and second %d\n", i);
                usleep(p);
            }
        }
    }
    return 0;
}