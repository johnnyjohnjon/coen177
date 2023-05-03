/* Name: HanDuan
* Date: February 9, 2023
* Title: Lab4 – Step 1
* Description: sample program that creates 20 threads, each of which print hello and sleep

None of the 20 threads complete their go function because the sleep(15) causes
each thread to switch to waiting, allowing the main thread to run to completion before
the threads finish running the go function. The program is terminated and the threads
are terminated before they run to completion.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
void *go(void *);
#define NTHREADS 20
pthread_t threads[NTHREADS];
int main()
{
    int i;
    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);

    printf("Main thread done.\n");
    return 0;
}
void *go(void *arg)
{
    printf("Hello from thread %d with iteration %d\n", (int)(unsigned long)pthread_self(), (int)(unsigned long)(size_t *)arg);
    sleep(15);
    pthread_exit(0);
}