// Name: Logan Calder
// Date: 09/30/2024
// Title: Lab2 – Part 7
// Description: This file contains a fork, which creates a child process. This process then runs the 'ls' command.

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
    pid = fork(); // Fork

    if (pid == -1) // Error catching
    {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }

    if (pid == 0) // Child runs ls command
    {
        execlp("/bin/ls", "ls", NULL);
    }

    else // Once child has terminated, parent exits
    {
        wait(NULL);
        printf("\n\nParent process. Child Complete\n");
        exit(0);
    }

    return 0;
}