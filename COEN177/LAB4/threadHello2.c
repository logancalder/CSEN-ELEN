// Name: Logan Calder
// Date: 10/15/2024
// Title: Lab4 – Part 2
// Description: This file contains a multiple threads program that prints out the thread ID and the thread number.

/**************************************************************
 *	threadHello.c - simple multi-threaded program.            *
 *   compile with: >gcc -lp threadHello.c -o threadHello       *                                              *
 **************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 20

void *go(void *);
pthread_t threads[NTHREADS];

int main()
{
    static int i;
    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, &i);
    printf("Main thread done.\n");
}
void *go(void *arg)
{
    printf("Hello from thread %d with thread ID %d \n", *(int *)arg, (int)pthread_self());
    return (NULL);
}
