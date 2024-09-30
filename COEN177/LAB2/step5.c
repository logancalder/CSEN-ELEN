// Name: Logan Calder
// Date: 09/30/2024
// Title: Lab2 – Part 5
// Description: This file contains forks, which creates a child processes. Total processes are 7.
// If there are child processes, two are present. This is underdone by using modulus to wait for every two child processes.

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

    // 7 processes will be created

    printf("Parent\n");
    for (int i = 0; i < 4; i++)
    {
        pid_t pid = fork();

        if (pid == -1) // Error catching
        {
            fprintf(stderr, "can't fork, error %d\n", errno);
        }

        else if (pid == 0) // If is a child, say so
        {
            printf("Child process %d\n", i);
            usleep(n);
            exit(0);
        }

        // Parent process waits for every two child processes
        if (i % 2 == 1)
        {
            int status;
            wait(NULL);
            wait(NULL);
            printf("Parent\n");
        }
    }

    return 0;
}