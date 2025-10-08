/*
 * Name: Logan Calder
 * Date: 04/22/2025
 * Title: Talk to the Server
 * Description: This program implements a TCP client that connects to a server
 * and downloads HTML content from a specified URL.
 *
 * Usage: ./http_client <url>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <regex.h>

// < ---------------------------- Constants ------------------------------- >

#define BUFFER_SIZE 4096
#define MAX_URL_LENGTH 1024
#define MAX_HOST_LENGTH 256
#define MAX_PATH_LENGTH 1024

// < --------------------------- Input Handling ---------------------------- >

int parse_url(const char *url, char *host, char *path)
{
    regex_t regex;
    regmatch_t matches[3];
    const char *pattern = "http://([^/]+)(/.*)?";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "pattern failed\n");
        return 0;
    }

    if (regexec(&regex, url, 3, matches, 0) == 0)
    {
        // extract host
        int host_len = matches[1].rm_eo - matches[1].rm_so;
        strncpy(host, url + matches[1].rm_so, host_len);
        host[host_len] = '\0';

        // extract path
        if (matches[2].rm_so != -1)
        {
            int path_len = matches[2].rm_eo - matches[2].rm_so;
            strncpy(path, url + matches[2].rm_so, path_len);
            path[path_len] = '\0';
        }
        else
        {
            strcpy(path, "/index.html");
        }

        regfree(&regex);
        return 1;
    }

    regfree(&regex);
    return 0;
}

int main(int argc, char *argv[])
{
    // < ------------------------ URL Parsing Section ------------------------ >

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        fprintf(stderr, "Example: %s http://example.com/index.html\n", argv[0]);
        return 1;
    }

    char url[MAX_URL_LENGTH];
    char host[MAX_HOST_LENGTH];
    char path[MAX_PATH_LENGTH];

    strncpy(url, argv[1], MAX_URL_LENGTH - 1);
    url[MAX_URL_LENGTH - 1] = '\0';

    if (!parse_url(url, host, path))
    {
        fprintf(stderr, "Invalid URL format. Please use http://hostname/path format.\n");
        return 1;
    }

    printf("Host: %s\n", host);
    printf("Path: %s\n", path);

    // < ------------------------ Socket Creation Section ------------------------ >

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("Failed to create socket");
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(80); // HTTP port

    // resolving hostname
    struct hostent *server_info = gethostbyname(host);
    if (server_info == NULL)
    {
        fprintf(stderr, "Failed to resolve hostname\n");
        close(sock);
        exit(EXIT_FAILURE);
    }

    memcpy(&server.sin_addr, server_info->h_addr, server_info->h_length);

    // < ------------------------ Server Connection Section ------------------------ >

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) // Connecting Socket
    {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // HTTP GET req
    char request[BUFFER_SIZE];
    snprintf(request, BUFFER_SIZE,
             "GET %s HTTP/1.1\r\n"
             "Host: %s\r\n"
             "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3\r\n"
             "Connection: close\r\n"
             "\r\n",
             path, host);

    // send req to server
    if (send(sock, request, strlen(request), 0) < 0)
    {
        perror("Failed to send request");
        close(sock);
        return 1;
    }

    // receive response from server
    char buffer[BUFFER_SIZE];
    int bytes_received;

    printf("\nresponse:\n");
    while ((bytes_received = recv(sock, buffer, BUFFER_SIZE - 1, 0)) > 0) // Response Handling
    {
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
    }

    close(sock);
    return 0;
}
