// Name: Logan Calder
// Date: 10/09/2024
// Title: Lab3 – Part 5
// Description: This file uses a pipe to display what the user has input. It continiously asks for input until the user types "No", and
//              creates a pipe each time.

/**************************
 *   Lab3 - pipe()
 **************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// main
int main(int argc, char *argv[])
{
    int fds[2];
    char buff[60];
    int count;
    char input[60];

    // Check if an argument is passed
    if (argc > 1)
    {
        strcpy(input, argv[1]);
    }
    else
    {
        strcpy(input, "");
    }

    while (1)
    {
        pipe(fds);
        if (strcmp(input, "No") == 0)
        {
            break; // Exit the loop if input is "No"
        }

        // Fork to create the writer process
        if (fork() == 0)
        {
            printf("\nWriter on the upstream end of the pipe -> %d arguments \n", argc);
            close(fds[0]);                           // Close reading end in writer
            write(fds[1], input, strlen(input) + 1); // Write input to the pipe
            close(fds[1]);                           // Close writing end after writing
            exit(0);
        }
        else
        {
            // Parent process waits for the writer to finish
            wait(0);

            // Fork to create the reader process
            if (fork() == 0)
            {
                printf("\nReader on the downstream end of the pipe \n");
                close(fds[1]); // Close writing end in reader
                while ((count = read(fds[0], buff, sizeof(buff) - 1)) > 0)
                {
                    buff[count] = '\0'; // Null-terminate the buffer
                    printf("%s\n", buff);
                }
                close(fds[0]); // Close reading end after reading
                exit(0);
            }
            else
            {
                close(fds[1]);
                // Parent process waits for the reader to finish
                wait(0);
            }
        }

        // Close pipe in the parent process
        close(fds[0]);
        close(fds[1]);

        // Get user input again
        printf("Enter input (No to cancel): ");
        scanf("%59s", input);
        printf("You entered: %s\n", input);
    }

    return 0;
}
