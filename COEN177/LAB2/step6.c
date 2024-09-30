// Name: Logan Calder
// Date: 09/30/2024
// Title: Lab2 – Part 6
// Description: This file contains multithreading. Completes same task as step1.c, but uses two threads.

/*Sample C program for Lab assignment 1*/
#include <stdio.h>     /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* fork */
#include <stdlib.h>    /* atoi */
#include <errno.h>     /* errno */
#include <pthread.h>

/* main function with command-line arguments to pass */

void *func(int n) // Basic function for threads to call
{
    for (int i = 0; i < 100; i++)
    {
        printf("\t\t Thread task %d\n", i);
        usleep(n);
    }
};

int main(int argc, char *argv[])
{
    int i, n = atoi(argv[1]);
    pthread_t pthread1, pthread2; // Creating our thread addresses

    // Thread creation

    if (pthread_create(&pthread1, NULL, func, NULL)) // If this != 0, that signifies an error in creation.
    {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }

    if (pthread_create(&pthread2, NULL, func, NULL))
    {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    // Wait for thread termination

    if (pthread_join(pthread1, NULL)) // If this != 0, that signifies an error in waiting for completion.
    {
        fprintf(stderr, "Error joining thread 1\n");
        return 2;
    }
    if (pthread_join(pthread2, NULL))
    {
        fprintf(stderr, "Error joining thread 2\n");
        return 2;
    }

    return 0;
}