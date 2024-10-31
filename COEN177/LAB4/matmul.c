// Name : Logan Calder
// Date: 10/15/2024
// Title: Lab4 – Part 3
// Description: This file contains a matrix multiplication program that uses threads to multiply two matrices together.

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define N 10

void *matmul(void *);
pthread_t threads[N];

double A[N][N];
double B[N][N];
double C[N][N];

int main()
{

    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 20;
        }
    }

    for (int i = 0; i < N; i++)
        pthread_create(&threads[i], NULL, matmul, NULL);
    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%.0f ", C[i][j]);
        }
        printf("\n");
    }
}

void *matmul(void *arg)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
