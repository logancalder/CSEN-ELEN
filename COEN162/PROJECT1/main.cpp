#include <iostream>
#include <string>
#include <cstring>
#include <regex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

// Function to parse URL and extract host and path
bool parseUrl(const std::string &url, std::string &host, std::string &path)
{
    // Regular expression to match HTTP URLs
    std::regex urlRegex("http://([^/]+)(/.*)?");
    std::smatch matches;

    if (std::regex_match(url, matches, urlRegex))
    {
        host = matches[1].str();
        path = matches[2].str();

        // If path is empty, set it to "/"
        if (path.empty())
        {
            path = "/";
        }

        return true;
    }

    return false;
}

int main()
{
    std::string url;
    std::string host, path;

    // Get URL from user
    std::cout << "Enter the URL (e.g., http://example.com/index.html): ";
    std::getline(std::cin, url);

    // Parse the URL to extract host and path
    if (!parseUrl(url, host, path))
    {
        std::cerr << "Invalid URL format. Please use http://hostname/path format." << std::endl;
        return 1;
    }

    std::cout << "Host: " << host << std::endl;
    std::cout << "Path: " << path << std::endl;

    // Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // Set up server address structure
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(80); // HTTP port

    // Resolve hostname to IP address
    struct hostent *serverInfo = gethostbyname(host.c_str());
    if (serverInfo == NULL)
    {
        std::cerr << "Failed to resolve hostname" << std::endl;
        close(sock);
        return 1;
    }

    // Copy IP address to server structure
    memcpy(&server.sin_addr, serverInfo->h_addr, serverInfo->h_length);

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        std::cerr << "Connection failed" << std::endl;
        close(sock);
        return 1;
    }

    // Prepare HTTP GET request
    std::string request = "GET " + path + " HTTP/1.1\r\n";
    request += "Host: " + host + "\r\n";
    request += "Connection: close\r\n";
    request += "\r\n";

    // Send request
    if (send(sock, request.c_str(), request.length(), 0) < 0)
    {
        std::cerr << "Failed to send request" << std::endl;
        close(sock);
        return 1;
    }

    // Receive response
    char buffer[4096];
    std::string response;
    int bytesReceived;

    while ((bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0)
    {
        buffer[bytesReceived] = '\0';
        response += buffer;
    }

    // Display response
    std::cout << "\nResponse from server:\n"
              << response << std::endl;

    // Close socket
    close(sock);

    return 0;
}
