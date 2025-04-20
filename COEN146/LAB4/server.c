/*
 * Name: Logan Calder
 * Date: 01/25/2025
 * Title: Lab4 - UDP Server
 * Description: This program implements a UDP server that sends a requested file to a client.
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

void send_file(int server_fd, struct sockaddr_in *client_addr, socklen_t addr_len, const char *filename)
{
    int file = open(filename, O_RDONLY);
    if (file < 0)
    {
        perror("File open error");
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(file, buffer, BUFFER_SIZE)) > 0)
    {
        if (sendto(server_fd, buffer, bytes_read, 0, (struct sockaddr *)client_addr, addr_len) < 0)
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
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <port> <filename>\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Cannot create socket");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // explicitly bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Cannot bind");
        close(server_fd);
        return 1;
    }

    printf("Server listening on port %d...\n", port);

    // must specify client addr since UDP is connectionless
    recvfrom(server_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
    printf("Client request received, sending file...\n");

    send_file(server_fd, &client_addr, addr_len, argv[2]);

    close(server_fd);
    return 0;
}
