// Name: Logan Calder
// Date: 09/30/2024
// Title: Lab2 – Part 1
// Description: This file contains a fork, which creates a child process. Total processes are two.
// These processes run a loop that prints out a message and sleeps for a given amount of time, n.

/*Sample C program for Lab assignment 1*/
#include <stdio.h>     /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* fork */
#include <stdlib.h>    /* atoi */
#include <errno.h>     /* errno */
/* main function with command-line arguments to pass */
int main(int argc, char *argv[])
{
    pid_t pid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\n Before forking.\n");
    pid = fork();
    if (pid == -1)
    {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }
    if (pid)
    {
        // Parent process
        for (i = 0; i < 100; i++)
        {
            printf("\t \t \t Parent Process %d \n", i);
            usleep(n);
        }
    }
    else
    {
        // Child process
        for (i = 0; i < 100; i++)
        {
            printf("Child process %d\n", i);
            usleep(n);
        }
    }
    return 0;
}