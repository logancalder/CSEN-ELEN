/*
 * Name: Logan Calder
 * Date: 04/22/2025
 * Title: Web Proxy Server
 * Description: This program implements a web proxy that sits between browsers and web servers,
 * handling HTTP requests and responses. Uses threads for concurrent request handling.
 *
 * Usage: ./http_proxy <port>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <regex.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

// < ---------------------------- Constants ------------------------------- >

#define BUFFER_SIZE 4096
#define MAX_URL_LENGTH 1024
#define MAX_HOST_LENGTH 256
#define MAX_PATH_LENGTH 1024
#define MAX_REQUEST_LENGTH 4096
#define BACKLOG 10
#define MAX_THREADS 100

// < --------------------------- Thread Management ---------------------------- >

pthread_t threads[MAX_THREADS];
int thread_count = 0;
pthread_mutex_t thread_mutex = PTHREAD_MUTEX_INITIALIZER;

void cleanup_thread(pthread_t thread_id) // thread cleanup (using thrads for optimization)
{
    pthread_mutex_lock(&thread_mutex);
    for (int i = 0; i < thread_count; i++)
    {
        if (pthread_equal(threads[i], thread_id))
        {
            for (int j = i; j < thread_count - 1; j++)
            {
                threads[j] = threads[j + 1];
            }
            thread_count--;
            break;
        }
    }
    pthread_mutex_unlock(&thread_mutex);
}

// < --------------------------- Request Parsing ---------------------------- >

int parse_http_request(const char *request, char *host, char *path, char *method)
{
    regex_t regex;
    regmatch_t matches[4];
    const char *pattern = "^(GET|POST|HEAD) http://([^/]+)(/.*)? HTTP/1\\.[01]";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Pattern compilation failed\n");
        return 0;
    }

    if (regexec(&regex, request, 4, matches, 0) == 0)
    {
        // extract method
        int method_len = matches[1].rm_eo - matches[1].rm_so;
        strncpy(method, request + matches[1].rm_so, method_len);
        method[method_len] = '\0';

        // extracting host
        int host_len = matches[2].rm_eo - matches[2].rm_so;
        strncpy(host, request + matches[2].rm_so, host_len);
        host[host_len] = '\0';

        // extracting path
        if (matches[3].rm_so != -1)
        {
            int path_len = matches[3].rm_eo - matches[3].rm_so;
            strncpy(path, request + matches[3].rm_so, path_len);
            path[path_len] = '\0';
        }
        else
        {
            strcpy(path, "/");
        }

        regfree(&regex);
        return 1;
    }

    regfree(&regex);
    return 0;
}

// < --------------------------- Connection Handling ---------------------------- >

void *handle_client_thread(void *arg)
{
    int client_sock = *((int *)arg);
    free(arg);

    char buffer[BUFFER_SIZE];
    char host[MAX_HOST_LENGTH];
    char path[MAX_PATH_LENGTH];
    char method[10];
    int bytes_received;

    // receive request from browser
    bytes_received = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received <= 0)
    {
        close(client_sock);
        cleanup_thread(pthread_self());
        return NULL;
    }
    buffer[bytes_received] = '\0';

    printf("\nReceived request from browser:\n%s\n", buffer);

    // parse the request
    if (!parse_http_request(buffer, host, path, method))
    {
        fprintf(stderr, "Failed to parse HTTP request\n");
        close(client_sock);
        cleanup_thread(pthread_self());
        return NULL;
    }

    printf("Parsed request:\n");
    printf("Method: %s\n", method);
    printf("Host: %s\n", host);
    printf("Path: %s\n", path);

    // Create socket to connect to target server
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        perror("Failed to create server socket");
        close(client_sock);
        cleanup_thread(pthread_self());
        return NULL;
    }

    // connect to target server
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);

    struct hostent *server_info = gethostbyname(host);
    if (server_info == NULL)
    {
        fprintf(stderr, "Failed to resolve hostname: %s\n", host);
        close(server_sock);
        close(client_sock);
        cleanup_thread(pthread_self());
        return NULL;
    }

    memcpy(&server_addr.sin_addr, server_info->h_addr, server_info->h_length);

    if (connect(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Failed to connect to target server");
        close(server_sock);
        close(client_sock);
        cleanup_thread(pthread_self());
        return NULL;
    }

    printf("Connected to target server: %s\n", host);

    // frwd the request to the target server
    if (send(server_sock, buffer, bytes_received, 0) < 0)
    {
        perror("Failed to forward request to server");
        close(server_sock);
        close(client_sock);
        cleanup_thread(pthread_self());
        return NULL;
    }

    // receive response from server and frwd to browser
    while ((bytes_received = recv(server_sock, buffer, BUFFER_SIZE - 1, 0)) > 0)
    {
        buffer[bytes_received] = '\0';
        if (send(client_sock, buffer, bytes_received, 0) < 0)
        {
            perror("Failed to forward response to browser");
            break;
        }
    }

    close(server_sock);
    close(client_sock);
    cleanup_thread(pthread_self());
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        fprintf(stderr, "Example: %s 8080\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);
    if (port <= 0 || port > 65535)
    {
        fprintf(stderr, "Invalid port number. Please use a port between 1 and 65535.\n");
        return 1;
    }

    // create server socket
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        perror("Failed to create server socket");
        return 1;
    }

    // set socket options to reuse address
    int opt = 1;
    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("Failed to set socket options");
        close(server_sock);
        return 1;
    }

    // bind socket to port
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Failed to bind socket");
        close(server_sock);
        return 1;
    }

    // listen
    if (listen(server_sock, BACKLOG) < 0)
    {
        perror("Failed to listen on socket");
        close(server_sock);
        return 1;
    }

    printf("Proxy server listening on port %d...\n", port);

    // loop for main
    while (1)
    {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);

        if (client_sock < 0)
        {
            perror("Failed to accept connection");
            continue;
        }

        printf("New connection from %s:%d\n",
               inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port));

        // if max # threads
        pthread_mutex_lock(&thread_mutex);
        if (thread_count >= MAX_THREADS)
        {
            pthread_mutex_unlock(&thread_mutex);
            fprintf(stderr, "Maximum number of threads reached. Rejecting connection.\n");
            close(client_sock);
            continue;
        }

        int *client_sock_ptr = malloc(sizeof(int));
        if (client_sock_ptr == NULL)
        {
            pthread_mutex_unlock(&thread_mutex);
            perror("Failed to allocate memory for client socket");
            close(client_sock);
            continue;
        }
        *client_sock_ptr = client_sock;

        // client thread
        if (pthread_create(&threads[thread_count], NULL, handle_client_thread, client_sock_ptr) != 0)
        {
            pthread_mutex_unlock(&thread_mutex);
            perror("Failed to create thread");
            free(client_sock_ptr);
            close(client_sock);
            continue;
        }

        thread_count++;
        pthread_mutex_unlock(&thread_mutex);
    }

    // cleanup
    pthread_mutex_destroy(&thread_mutex);
    close(server_sock);
    return 0;
}
