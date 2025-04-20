/*
 * Name: Logan Calder
 * Date: 02/05/2025
 * Title: Lab5 - RDT3.0 UDP Server
 * Description: This program implements a UDP server that receives a file from a client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <time.h>

#define BUFFER_SIZE 10

typedef struct
{
    int seq_ack;
    int len;
    int checksum;
} Header;

typedef struct
{
    char data[10];
    Header header;
} Packet;

int calculate_checksum(Packet *packet)
{
    int checksum = 0;
    char *ptr = (char *)packet;
    char *end = ptr + sizeof(Header) + sizeof(packet); // Header + actual data
    while (ptr < end)
    {
        checksum ^= *ptr++;
    }
    return checksum;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <port> <dst_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    int port = atoi(argv[1]);
    char *dst_file = argv[2];

    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);
    Packet packet, ack_packet;

    // creating socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // UDP rdt3.0 receiver
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("srvr LIVE on port %d...\n", port);

    int file_fd = open(dst_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_fd == -1)
    {
        perror("File err");
        close(sockfd);
        return 1;
    }

    int expected_seq = 0;
    while (1)
    {
        ssize_t received = recvfrom(sockfd, &packet, sizeof(packet), 0,
                                    (struct sockaddr *)&client_addr, &addr_size);
        if (received < 0)
        {
            perror("failed");
            break;
        }

        printf("Received Packet: SEQ=%d, Checksum=%d\n", packet.header.seq_ack, packet.header.checksum);

        // simulating a packet loss using rand()
        if (rand() % 2 == 1)
        {
            packet.header.checksum = 0; // corrupt the packet
        }

        int computed_checksum = calculate_checksum(&packet);
        if (computed_checksum == packet.header.checksum && packet.header.seq_ack == expected_seq)
        {
            // write data using packet.header.len
            if (packet.header.len > 0)
            {
                write(file_fd, packet.data, packet.header.len);
            }
            else
            {
                printf("File transfer complete.\n");
                break;
            }

            // send ACK back to client
            ack_packet.header.seq_ack = expected_seq;
            ack_packet.header.len = 0;
            ack_packet.header.checksum = calculate_checksum(&ack_packet);
            sendto(sockfd, &ack_packet, sizeof(ack_packet), 0,
                   (struct sockaddr *)&client_addr, addr_size);
            printf("sent ACK %d\n", ack_packet.header.seq_ack);

            expected_seq = 1 - expected_seq;
        }
        else
        {
            printf("checksum failed. Resending last ACK.\n");
            sendto(sockfd, &ack_packet, sizeof(ack_packet), 0,
                   (struct sockaddr *)&client_addr, addr_size);
        }
    }

    close(file_fd);
    close(sockfd);
    return 0;
}
