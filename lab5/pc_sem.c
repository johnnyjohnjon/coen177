#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define BUFSIZE 10
#define NP 3
#define NC 2

pthread_t tidP[NP], tidC[NC];
int buff[BUFSIZE];
sem_t *mutex, *full, *empty;
int p, c, in, out;

void *producer(void *arg)
{
    int item;
    int p = (int)(unsigned long)arg;
    srand(time(0));
    do
    {
        item = (rand() % 100);
        sem_wait(empty);
        sem_wait(mutex);
        buff[in] = item;
        printf("Producer #: %d produced item: %d at buffer space: %d\n", p, item);
        sleep(5);
        in = (in + 1) % BUFSIZE;
        sem_post(mutex);
        sem_post(full);
    } while (1);
    return (NULL);
}

void *consumer(void *arg)
{
    int item;
    int c = (int)(unsigned long)arg;
    srand(time(0));
    do
    {
        sem_wait(full);
        sem_wait(mutex);
        item = buff[out];
        printf("\t\t\tConsumer #: %d consumed item: %d at buffer space: %d\n", p, item);
        sleep(10);
        out = (out + 1) % BUFSIZE;
        sem_post(mutex);
        sem_post(empty);
    } while (1);
    return (NULL);
}
void cleanup(int sigtype)
{
    sem_unlink("mutex");
    sem_unlink("full");
    sem_unlink("empty");
    printf("\n Terminating\n");
    exit(0);
}
int main()
{
    signal(SIGINT, cleanup);
    mutex = sem_open("mutex", O_CREAT, 0644, 1);
    empty = sem_open("empty", O_CREAT < 0644, BUFSIZE);
    full = sem_open("full", O_CREAT, 0644, 0);
    for (p = 0; p < NP; p++)
    {
        pthread_create(&tidP[p], NULL, producer, (void *)(size_t)p);
    }
    for (c = 0; c < NC; c++)
    {
        pthread_create(&tidC[c], NULL, consumer, (void *)(size_t)c);
    }
    for (p = 0; p < NP; p++)
    {
        pthread_join(tidP[p], NULL);
        printf("Producer thread %d returned\n", p);
    }
    for (c = 0; c < NC; c++)
    {
        pthread_join(tidC[c], NULL);
        printf("\t\t\tConsumer thread %d returned\n", c);
    }
    for (;;)
        ;
    return 0;
}