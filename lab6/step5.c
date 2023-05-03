
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

char ogfile[20];
char newfile[20];

int BUFFSIZE;
int NTHREADS;

void *copies(void *arg)
{
    char buffer[BUFFSIZE];
    sprintf(newfile, "output%d.txt", BUFFSIZE);
    FILE *fp = fopen(ogfile, "rb");
    FILE *fpout = fopen(newfile, "wb");
    while (fread(buffer, BUFFSIZE, 1, fp))
    {
        fwrite(buffer, BUFFSIZE, 1, fpout);
    }
    fclose(fp);
    fclose(fpout);
    return 0;
}

int main(int argc, char *argv[])
{
    strcpy(ogfile, argv[1]);
    BUFFSIZE = atoi(argv[2]);
    NTHREADS = atoi(argv[3]);
    pthread_t threads[NTHREADS];
    int i;

    for (i = 0; i < NTHREADS; i++)
    {
        pthread_create(&threads[i], NULL, copies, (void *)(size_t)i);
    }
    for (i = 0; i < NTHREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    return 0;
}