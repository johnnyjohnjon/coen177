/* Name: Han Duan
* Date: February 9, 2023
* Title: Lab4 – Step 4
* Description: program accepts three arguments for the dimensions of the input matrices.
    It then generates 2 input matrices and creates threads for each row of the resulting
    matrix and calculates the product of the two input matrices.
*
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_NUM 11

// A, B, C matrices
double **matrixA, **matrixB, **matrixC;
int N, M, L;

void *multiplyMatrixRow(void *arg);
int max(int a, int b);

int main(int argc, char *argv[])
{
    // ensure right number of arguments
    if (argc != 4)
    {
        printf("Usage: %s <N> <M> <L>\n", argv[0]);
        exit(0);
    }

    // grab dimensions from input
    int i, j;
    M = atoi(argv[2]);
    N = atoi(argv[1]);
    L = atoi(argv[3]);
    pthread_t threads[N];

    // create and allocate random matrices
    matrixA = malloc(sizeof(double *) * N); // allocate number of rows
    matrixB = malloc(sizeof(double *) * M);
    matrixC = malloc(sizeof(double *) * N);

    // create matrix A
    srand(time(NULL));
    printf("Matrix A:\n");
    for (i = 0; i < N; i++)
    {
        matrixA[i] = malloc(sizeof(double) * M); // allocate each cell in row
        for (j = 0; j < M; j++)
        {
            matrixA[i][j] = rand() % MAX_NUM;
            printf("%g\t", matrixA[i][j]);
        }

        printf("\n");
    }

    // create matrix B
    printf("\nMatrix B:\n");
    for (i = 0; i < M; i++)
    {
        matrixB[i] = malloc(sizeof(double) * L);
        for (j = 0; j < L; j++)
        {
            matrixB[i][j] = rand() % MAX_NUM;
            printf("%g\t", matrixB[i][j]);
        }

        printf("\n");
    }

    // allocate matrix c rows
    for (i = 0; i < N; ++i)
        matrixC[i] = malloc(sizeof(double) * L);

    // create threads that calculate matrixC, one for each row in N
    for (i = 0; i < N; ++i)
    {
        pthread_create(&threads[i], NULL, multiplyMatrixRow, (void *)(size_t)i);
    }

    // join all threads
    for (i = 0; i < N; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    // print output
    printf("\nMatrix C:\n");
    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < L; ++j)
            printf("%g\t", matrixC[i][j]);
        printf("\n");
    }

    // free memory before exiting
    int longestRow = max(max(N, M), L);
    for (i = 0; i < longestRow; ++i)
    {
        if (i < N)
        {
            free(matrixA[i]);
            free(matrixC[i]);
        }

        if (i < M)
            free(matrixB[i]);
    }

    free(matrixA);
    free(matrixB);
    free(matrixC);

    return 0;
}

int max(int a, int b)
{
    if (a > b)
        return a;

    return b;
}

void *multiplyMatrixRow(void *arg)
{
    int i = (int)(unsigned long)(size_t *)arg;
    int j, k;

    for (j = 0; j < L; j++)
    {
        double temp = 0;
        for (k = 0; k < M; k++)
        {
            temp += matrixA[i][k] * matrixB[k][j];
        }
        matrixC[i][j] = temp;
    }

    pthread_exit(0);
}