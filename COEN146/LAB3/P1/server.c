/*
 * Name: Logan Calder
 * Date: 01/25/2025
 * Title: Lab3 - TCP Server
 * Description: This program implements a TCP server that accepts a client connection
 * and transfers a requested file over the connection.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

void send_file(int client_socket, const char *filename)
{
    int file = open(filename, O_RDONLY);
    if (file < 0)
    {
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(file, buffer, BUFFER_SIZE)) > 0)
    {
        if (send(client_socket, buffer, bytes_read, 0) < 0)
        {
            perror("Send error");
            break;
        }
    }

    close(file);
    printf("File transfer completed.\n");
}

int main(int argc, char *argv[])
{
    int port = atoi(argv[1]);
    int server_fd, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("cannot create socket");
        return 0;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("cannot bind");
        close(server_fd);
        return 0;
    }

    if (listen(server_fd, 5) < 0)
    {
        perror("cannot listen");
        close(server_fd);
        return 0;
    }

    printf("Server listening on port %d...\n", port);

    if ((client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len)) < 0)
    {
        close(server_fd);
        return 0;
    }

    printf("Client accepted & is connected.\n");

    send_file(client_socket, argv[2]);

    printf("Sent file!\n");

    close(client_socket);
    close(server_fd);
    return 0;
}
