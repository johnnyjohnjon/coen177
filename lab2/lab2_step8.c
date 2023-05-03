

// Name: Han Duan
// Date: 1/26/2023
// Lab2 P8
// Description: threads
#include <stdio.h>     /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* fork */
#include <stdlib.h>    /* atoi */
#include <errno.h>     /* errno */
#include <pthread.h>

void *parent(void *x)
{
    for (int i = 0; i < 10; i++)
    {
        printf("\t \t \t I am the parent Process displaying iteration %d \n", i);
        usleep(3000);
    }
    pthread_exit(NULL);
}

void *child(void *x)
{
    for (int i = 0; i < 10; i++)
    {
        printf("I am the child Process displaying iteration %d \n", i);
        usleep(3000);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t thread_1, thread_2;
    pthread_create(&thread_1, NULL, parent, NULL);
    pthread_create(&thread_2, NULL, child, NULL);
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    pthread_exit(NULL);
    return 0;
}