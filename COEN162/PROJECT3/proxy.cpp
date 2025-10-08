/*
 * Name: Logan Calder
 * Date: 04/22/2025
 * Title: Web Proxy Server with Cache
 * Description: This program implements a web proxy that sits between browsers and web servers,
 * handling HTTP requests and responses. Uses threads for concurrent request handling and
 * implements caching with conditional GET requests.
 *
 * Usage: ./proxy
 */

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <algorithm>
#include <list>
#include <memory>
#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <thread>
#include <mutex>
#include <sstream>
#include <iomanip>
#include <vector>
#include <set>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::lock_guard;
using std::mutex;
using std::ofstream;
using std::ostringstream;
using std::set;
using std::string;
using std::thread;
using std::unordered_map;
namespace fs = std::filesystem;

// < ---------------------------- Constants ------------------------------- >

const int LISTEN_PORT = 8080;
const int DATA_BUFFER_SIZE = 4096;
const string STORAGE_PATH = "./cache/";
set<string> cachedHosts; // Stores host+path combinations for cached content

// < --------------------------- Global Variables ---------------------------- >

mutex consoleLock;
mutex storageLock;
unordered_map<string, string> modificationTimes; // host+path -> last-modified timestamp

// < --------------------------- Utility Functions ---------------------------- >

/*
 * Outputs messages to console with thread safety
 * Errors are prefixed with ERROR
 * Regular messages are prefixed with INFO
 */
void consoleOutput(const string &msg, bool isErr = false)
{
    lock_guard<mutex> guard(consoleLock);
    if (isErr)
    {
        printf("ERROR: %s\n", msg.c_str());
    }
    else
    {
        printf("INFO: %s\n", msg.c_str());
    }
}

// < --------------------------- Network Functions ---------------------------- >

/*
 * Converts hostname to IP address
 * Returns IP address on success, empty string on failure
 */
string getIPFromHostname(const string &host)
{
    struct hostent *dnsEntry = gethostbyname(host.c_str());
    if (dnsEntry == nullptr)
    {
        consoleOutput("DNS resolution failed for: " + host, true);
        return "";
    }

    char ipStr[INET_ADDRSTRLEN];
    struct in_addr **addrArray = (struct in_addr **)dnsEntry->h_addr_list;

    if (addrArray[0] != nullptr)
    {
        inet_ntop(AF_INET, addrArray[0], ipStr, INET_ADDRSTRLEN);
        return string(ipStr);
    }

    return "";
}

/*
 * Establishes connection to target server
 * Returns socket descriptor on success, -1 on failure
 */
int establishConnection(const string &targetIP)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        consoleOutput("Socket creation failed", true);
        return -1;
    }

    struct sockaddr_in targetAddr;
    memset(&targetAddr, 0, sizeof(targetAddr));
    targetAddr.sin_family = AF_INET;
    targetAddr.sin_port = htons(80);

    if (inet_pton(AF_INET, targetIP.c_str(), &targetAddr.sin_addr) <= 0)
    {
        consoleOutput("Invalid IP: " + targetIP, true);
        close(sock);
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&targetAddr, sizeof(targetAddr)) < 0)
    {
        consoleOutput("Connection failed: " + targetIP, true);
        close(sock);
        return -1;
    }

    return sock;
}

/*
 * Initializes listening socket
 * Returns socket descriptor on success, -1 on failure
 */
int initListener(int port)
{
    int listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
    {
        consoleOutput("Listener socket creation failed", true);
        return -1;
    }

    int reuse = 1;
    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (::bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0 || listen(listener, 10) < 0)
    {
        consoleOutput("Socket bind/listen failed", true);
        close(listener);
        return -1;
    }

    return listener;
}

// < --------------------------- Request Processing ---------------------------- >

/*
 * Analyzes HTTP request to extract host and path
 * Returns true if successful, false otherwise
 */
bool analyzeRequest(const string &req, string &host, string &path)
{
    size_t headerEnd = req.find("\r\n");
    if (headerEnd == string::npos)
        return false;

    string firstLine = req.substr(0, headerEnd);
    size_t pathBegin = firstLine.find(" "), pathEnd = firstLine.find(" ", pathBegin + 1);
    if (pathBegin == string::npos || pathEnd == string::npos)
        return false;

    path = firstLine.substr(pathBegin + 1, pathEnd - pathBegin - 1);
    if (path.empty())
        path = "/";

    size_t hostBegin = req.find("Host: ");
    if (hostBegin == string::npos)
    {
        hostBegin = req.find("host: ");
        if (hostBegin == string::npos)
            return false;
    }

    size_t hostEnd = req.find("\r\n", hostBegin);
    host = req.substr(hostBegin + 6, hostEnd - hostBegin - 6);

    // Clean up host string
    if (host.find("http://") == 0)
        host = host.substr(7);
    else if (host.find("https://") == 0)
        host = host.substr(8);

    size_t portPos = host.find(":");
    if (portPos != string::npos)
        host = host.substr(0, portPos);

    return true;
}

// < --------------------------- Cache Management ---------------------------- >

/*
 * Generates storage path for cached content
 * Returns the storage path
 */
string generateStoragePath(const string &host, const string &path)
{
    string key = host + path;
    replace(key.begin(), key.end(), '/', '_');
    replace(key.begin(), key.end(), '.', '_');
    return STORAGE_PATH + key + ".html";
}

/*
 * Checks if content is cached
 * Returns true if cached, false otherwise
 */
bool isContentCached(const string &host, const string &path)
{
    string key = host + path;
    return cachedHosts.find(key) != cachedHosts.end(); // if its in the set
}

/*
 * Extracts modification time from response headers
 * Returns the modification time
 */
string getModificationTime(const string &headers)
{
    istringstream stream(headers);
    string line;
    while (getline(stream, line))
    {
        if (line.find("Last-Modified:") != string::npos)
        {
            return line.substr(line.find(":") + 2);
        }
    }
    return "";
}

/*
 * Creates conditional request with modification time
 * Returns the modified request
 */
string createConditionalRequest(const string &req, const string &modTime)
{
    string modified = req;
    modified.insert(modified.find("\r\n") + 2, "If-Modified-Since: " + modTime + "\r\n");
    return modified;
}

// < --------------------------- Request Handler ---------------------------- >

/*
 * Processes client request
 */
void processRequest(int clientSock)
{
    char buffer[DATA_BUFFER_SIZE];
    struct timeval timeout = {10, 0};
    setsockopt(clientSock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    ssize_t received = recv(clientSock, buffer, DATA_BUFFER_SIZE - 1, 0);
    if (received <= 0)
    {
        consoleOutput("Failed to receive request from client", true);
        close(clientSock);
        return;
    }
    buffer[received] = '\0';
    string request(buffer);

    string host, path;
    if (!analyzeRequest(request, host, path))
    {
        consoleOutput("Failed to analyze request", true);
        close(clientSock);
        return;
    }
    consoleOutput("Processing request: " + host + path);

    // Ensure cache directory exists
    if (!fs::exists(STORAGE_PATH))
    {
        try
        {
            fs::create_directories(STORAGE_PATH);
        }
        catch (const fs::filesystem_error &e)
        {
            consoleOutput("Failed to create cache directory: " + string(e.what()), true);
            close(clientSock);
            return;
        }
    }

    string storagePath = generateStoragePath(host, path);
    string serverIP = getIPFromHostname(host);
    if (serverIP.empty())
    {
        consoleOutput("Failed to resolve hostname: " + host, true);
        close(clientSock);
        return;
    }

    string httpReq = "GET " + path + " HTTP/1.1\r\nHost: " + host + "\r\nUser-Agent: Mozilla/5.0\r\nConnection: close\r\n\r\n";

    {
        lock_guard<mutex> guard(storageLock);
        if (isContentCached(host, path))
        {
            consoleOutput("✅ CACHE HIT for: " + host + path);
            consoleOutput("==========================================");
            string modTime = modificationTimes[host + path];
            if (!modTime.empty())
            {
                httpReq = createConditionalRequest(httpReq, modTime);
                consoleOutput("📝 Sent conditional GET with If-Modified-Since: " + modTime);
            }
        }
        else
        {
            consoleOutput("❌ CACHE MISS for: " + host + path);
            consoleOutput("==========================================");
        }
    }

    int serverSock = establishConnection(serverIP);
    if (serverSock < 0)
    {
        consoleOutput("Failed to establish connection to server", true);
        close(clientSock);
        return;
    }
    setsockopt(serverSock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    if (send(serverSock, httpReq.c_str(), httpReq.length(), 0) < 0)
    {
        consoleOutput("Failed to send request to server", true);
        close(serverSock);
        close(clientSock);
        return;
    }
    shutdown(serverSock, SHUT_WR);

    string response;
    string headers;
    bool headersComplete = false;
    size_t contentStart = 0;

    while ((received = recv(serverSock, buffer, DATA_BUFFER_SIZE - 1, 0)) > 0)
    {
        buffer[received] = '\0';
        response.append(buffer, received);

        if (!headersComplete)
        {
            size_t headerEnd = response.find("\r\n\r\n");
            if (headerEnd != string::npos)
            {
                headers = response.substr(0, headerEnd + 4);
                contentStart = headerEnd + 4;
                headersComplete = true;
            }
        }

        if (send(clientSock, buffer, received, 0) < 0)
        {
            consoleOutput("Failed to send response to client", true);
            close(serverSock);
            close(clientSock);
            return;
        }
    }

    if (response.find("403 Forbidden") != string::npos)
    {
        consoleOutput("Server denied access");
    }
    else if (response.find("404 Not Found") != string::npos)
    {
        consoleOutput("Resource not found on server");
    }
    else if (response.find("304 Not Modified") != string::npos)
    {
        consoleOutput("Using cached version");
        ifstream cache(storagePath, std::ios::binary);
        if (cache.is_open())
        {
            ostringstream content;
            content << cache.rdbuf();
            string cached = content.str();
            if (send(clientSock, cached.c_str(), cached.size(), 0) < 0)
            {
                consoleOutput("Failed to send cached content to client", true);
            }
        }
        else
        {
            consoleOutput("Failed to read from cache", true);
        }
    }
    else if (response.find("200 OK") != string::npos)
    {
        consoleOutput("Updating cache with new content");
        if (headersComplete)
        {
            try
            {
                ofstream cache(storagePath, std::ios::binary);
                if (cache.is_open())
                {
                    cache << response.substr(contentStart);
                    cache.close();

                    string modTime = getModificationTime(headers);
                    if (!modTime.empty())
                    {
                        lock_guard<mutex> guard(storageLock);
                        modificationTimes[host + path] = modTime;
                        cachedHosts.insert(host + path);
                    }
                }
                else
                {
                    consoleOutput("Failed to write to cache", true);
                }
            }
            catch (const std::exception &e)
            {
                consoleOutput("Error writing to cache: " + string(e.what()), true);
            }
        }
    }

    consoleOutput("Request completed: " + host + path);
    close(serverSock);
    close(clientSock);
}

// < --------------------------- Main Function ---------------------------- >

/*
 * Main function to start the HTTP proxy server
 */
int main()
{
    // Clear cache directory before starting
    try
    {
        for (const auto &entry : fs::directory_iterator(STORAGE_PATH))
        {
            fs::remove(entry.path());
        }
        consoleOutput("Cache directory cleared");
    }
    catch (const fs::filesystem_error &e)
    {
        consoleOutput("Failed to clear cache: " + string(e.what()), true);
        return 1;
    }
    consoleOutput("Proxy server starting on port " + std::to_string(LISTEN_PORT));
    int listener = initListener(LISTEN_PORT);
    if (listener < 0)
        return 1;

    while (true)
    {
        struct sockaddr_in clientAddr;
        socklen_t addrLen = sizeof(clientAddr);
        int clientSock = accept(listener, (struct sockaddr *)&clientAddr, &addrLen);
        if (clientSock < 0)
            continue;
        thread(processRequest, clientSock).detach();
    }

    close(listener);
    return 0;
}
