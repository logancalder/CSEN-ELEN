// Name: Logan Calder
// Date: 10/09/2024
// Title: Lab3 – Part 7
// Description: The fixed thread code, which properly allocates memory for each thread's argument.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];

int main()
{
    int i;
    for (i = 0; i < NTHREADS; i++)
    {
        int *arg = malloc(sizeof(*arg)); // Allocate memory for each thread's argument
        *arg = i;
        pthread_create(&threads[i], NULL, go, arg);
    }
    for (i = 0; i < NTHREADS; i++)
    {
        pthread_join(threads[i], NULL);
        printf("Thread %d returned\n", i);
    }
    printf("Main thread done.\n");
    return 0;
}

void *go(void *arg)
{
    int iteration = *(int *)arg;
    printf("Hello from thread %ld with iteration %d\n", (long)pthread_self(), iteration);
    free(arg); // Free allocated memory
    return 0;
}
