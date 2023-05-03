
// Name: Han Duan
// Date: 1/26/2023
// Lab2 P6
// Description: Child Proccess performs ls command and parent proccess waits to exit

#include <pthread.h>
#include <stdio.h>     /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* fork */
#include <stdlib.h>    /* atoi */
#include <errno.h>     /* errno */
/* main function*/

int main(int argc, char *argv[])
{
    pid_t pid1, pid2, pid3, pid4, pid5, pid6, pid7;
    int i, n = atoi(argv[1]), m = atoi(argv[2]), o = atoi(argv[3]), p = atoi(argv[4]), q = atoi(argv[5]), r = atoi(argv[6]), s = atoi(argv[7]);
    printf("\n Before forking.\n");
    pid1 = fork();

    if (pid1 < 0)
    {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }

    if (pid1)
    {
        pid2 = fork();
        if (pid2)
        {
            printf("This is process pid=%d, the parent process is ppid=%d\n", getpid(), getppid());
            usleep(n);
        }
        else
        {
            pid3 = fork();
            if (pid3)
            {
                pid4 = fork();
                if (pid4)
                {
                    printf("This is process pid=%d, the parent process is ppid=%d\n", getpid(), getppid());
                    usleep(m);
                }
                else
                {
                    printf("This is process pid=%d, the parent process is ppid=%d\n", getpid(), getppid());
                    usleep(o);
                }
            }
            else
            {
                printf("This is process pid=%d, the parent process is ppid=%d\n", getpid(), getppid());
                usleep(p);
            }
        }
    }
    else
    {
        pid5 = fork();
        if (pid5)
        {
            pid6 = fork();
            if (pid6)
            {
                printf("This is process pid=%d, the parent process is ppid=%d\n", getpid(), getppid());
                usleep(q);
            }
            else
            {
                printf("This is process pid=%d, the parent process is ppid=%d\n", getpid(), getppid());
                usleep(r);
            }
        }
        else
        {
            printf("This is process pid=%d, the parent process is ppid=%d\n", getpid(), getppid());
            usleep(s);
        }
    }
}