/*
 * Name: Logan Calder
 * Date: 01/25/2025
 * Title: Lab3 - TCP Client
 * Description: This program implements a TCP client that connects to a server
 * and downloads a requested file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void receive_file(int socket, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        perror("File open error");
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    while ((bytes_received = recv(socket, buffer, BUFFER_SIZE, 0)) > 0)
    {
        fwrite(buffer, 1, bytes_received, file);
    }

    if (bytes_received < 0)
    {
        perror("Receive error");
    }
    else
    {
        printf("File transfer completed. Saved as %s\n", filename);
    }

    fclose(file);
}

int main(int argc, char *argv[])
{
    int port = atoi(argv[1]);
    int client_socket;
    struct sockaddr_in server_addr;

    // Create client socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0)
    {
        perror("Invalid address");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Connection failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server. Receiving file...\n");

    // Receive file from server
    receive_file(client_socket, argv[2]);

    printf("Received.\n");

    close(client_socket);
    return 0;
}
