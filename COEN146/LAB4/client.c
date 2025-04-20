/*
 * Name: Logan Calder
 * Date: 01/25/2025
 * Title: Lab4 - UDP Client
 * Description: This program implements a UDP client that requests a file from a server
 * and downloads it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void receive_file(int socket, struct sockaddr_in *server_addr, socklen_t addr_len, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        perror("File open error");
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    while ((bytes_received = recvfrom(socket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)server_addr, &addr_len)) > 0)
    {
        fwrite(buffer, 1, bytes_received, file);
        if (bytes_received < BUFFER_SIZE)
            break;
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
    socklen_t addr_len = sizeof(server_addr);

    // Create UDP socket
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
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

    // specify server addr since UDP is connectionless
    sendto(client_socket, argv[2], strlen(argv[2]) + 1, 0, (struct sockaddr *)&server_addr, addr_len);
    printf("Requested file: %s\n", argv[2]);

    // Receive file from server
    receive_file(client_socket, &server_addr, addr_len, argv[2]);

    printf("Received.\n");

    close(client_socket);
    return 0;
}
