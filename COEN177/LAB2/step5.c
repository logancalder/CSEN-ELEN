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
#include <stdbool.h>
/* main function with command-line arguments to pass */

int main(int argc, char *argv[])
{
    pid_t pid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\n Before forking.\n");

    // 7 processes will be created

    pid_t pid_list[2];

    int generation = 0;
    int children = 0;
    bool should_make_children = true;

    // printf("PARENT Parent PID: %d My PID: %d Some children\n", getppid(), getpid());
    while (1)
    {
        pid_t pid = fork();

        if (pid == -1) // Error catching
        {
            fprintf(stderr, "can't fork, error %d\n", errno);
        }

        else if (pid == 0) // If is a child, say so
        {
            children = 0;
            generation++;
            if (generation >= 3)
            {
                printf("CHILD My PID: %d Parent PID: %d  No children\n", getpid(), getppid());
                break;
            }
            if (should_make_children)
            {
                continue;
            }
            else
            {
                printf("CHILD My PID: %d Parent PID: %d  No Children\n", getpid(), getppid());
                break;
            }
        }
        else
        {
            children++;
            should_make_children = false;
            if (children == 2)
            {
                printf("PARENT My PID: %d Parent PID: %d Children %d %d\n", getpid(), getppid(), wait(0), wait(0));
                break;
            }
        }
    }

    return 0;
}