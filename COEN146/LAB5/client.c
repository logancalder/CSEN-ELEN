/*
 * Name: Logan Calder
 * Date: 02/05/2025
 * Title: Lab5 - RDT3.0 UDP Client
 * Description: This program implements a UDP client that sends a file to a server
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
        fprintf(stderr, "Usage: %s <port> <src_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    int port = atoi(argv[1]);
    char *src_file = argv[2];

    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_size = sizeof(server_addr);
    Packet packet, ack_packet;

    // creating socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // setting up UDP specific info
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // opening file
    int file_fd = open(src_file, O_RDONLY);
    if (file_fd == -1)
    {
        perror("file not found");
        close(sockfd);
        return 1;
    }

    int seq_num = 0;
    ssize_t bytes_read;
    struct timeval tv;
    fd_set readfds;

    // loop to send packets to srvr
    while ((bytes_read = read(file_fd, packet.data, BUFFER_SIZE)) > 0)
    {
        packet.header.seq_ack = seq_num;
        packet.header.len = bytes_read;
        packet.header.checksum = calculate_checksum(&packet);

        while (1)
        {
            sendto(sockfd, &packet, sizeof(packet), 0,
                   (struct sockaddr *)&server_addr, addr_size);
            printf("Sent Packet: SEQ=%d, Checksum=%d\n", packet.header.seq_ack, packet.header.checksum); // debug info

            // UDP rdt3.0 timeout and retransmit
            FD_ZERO(&readfds);
            FD_SET(sockfd, &readfds);
            tv.tv_sec = 1;
            tv.tv_usec = 0;

            int rv = select(sockfd + 1, &readfds, NULL, NULL, &tv);
            if (rv == 0)
            {
                printf("Timeout, resending packet SEQ=%d\n", seq_num);
            }
            else
            {
                recvfrom(sockfd, &ack_packet, sizeof(ack_packet), 0,
                         (struct sockaddr *)&server_addr, &addr_size);
                printf("Received ACK %d, Checksum=%d\n", ack_packet.header.seq_ack, ack_packet.header.checksum);

                if (ack_packet.header.seq_ack == seq_num)
                {
                    seq_num = 1 - seq_num;
                    break;
                }
            }
        }
    }

    // send EOF packet
    packet.header.len = 0;
    packet.header.checksum = calculate_checksum(&packet);
    for (int i = 0; i < 3; i++)
    {
        sendto(sockfd, &packet, sizeof(packet), 0,
               (struct sockaddr *)&server_addr, addr_size);
        printf("Sent EOF Packet\n");

        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        int rv = select(sockfd + 1, &readfds, NULL, NULL, &tv);
        if (rv == 0)
        {
            printf("Timeout, resending EOF\n");
        }
        else
        {
            recvfrom(sockfd, &ack_packet, sizeof(ack_packet), 0,
                     (struct sockaddr *)&server_addr, &addr_size);
            if (ack_packet.header.seq_ack == seq_num)
            {
                break;
            }
        }
    }

    close(file_fd);
    close(sockfd);
    return 0;
}
