/*
 * Name: Logan Calder
 * Date: 01/25/2025
 * Title: Lab3 - Multithreaded TCP Server
 * Description: This program implements a multithreaded TCP server that accepts client connections
 * and transfers a requested file over the connection.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

// Struct to hold thread arguments
typedef struct
{
    int client_socket;
    const char *file_name;
} ThreadArgs;

void *handle_client(void *arg)
{
    ThreadArgs *thread_args = (ThreadArgs *)arg; // Cast the argument to ThreadArgs
    int client_socket = thread_args->client_socket;
    const char *filename = thread_args->file_name;

    free(thread_args); // Free allocated memory for the arguments

    printf("Client connected. Handling file transfer for %s.\n", filename);

    // Open the specified file
    int file = open(filename, O_RDONLY);
    if (file < 0)
    {
        perror("File open error");
        close(client_socket);
        return NULL;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Read and send the file data to the client
    while ((bytes_read = read(file, buffer, BUFFER_SIZE)) > 0)
    {
        if (send(client_socket, buffer, bytes_read, 0) < 0)
        {
            perror("Send error");
            break;
        }
    }

    close(file);
    close(client_socket);

    printf("File transfer to client completed. Connection closed.\n");

    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <port> <file_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
    const char *file_name = argv[2]; // Get file name from argv

    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0)
    {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", port);

    while (1)
    {
        int *client_socket = malloc(sizeof(int));
        if (!client_socket)
        {
            continue;
        }

        *client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (*client_socket < 0)
        {
            free(client_socket);
            continue;
        }

        // malloc for thread
        ThreadArgs *thread_args = malloc(sizeof(ThreadArgs));
        if (!thread_args)
        {
            perror("Memory allocation failed");
            close(*client_socket);
            free(client_socket);
            continue;
        }

        thread_args->client_socket = *client_socket;
        thread_args->file_name = file_name;

        // multithreading
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, thread_args) != 0)
        {
            perror("Thread creation failed");
            close(*client_socket);
            free(client_socket);
            free(thread_args);
        }
        else
        {
            pthread_detach(thread_id); // Detach the thread
        }
    }

    close(server_fd);
    return 0;
}
