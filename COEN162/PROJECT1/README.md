# HTTP Client

This is a simple HTTP client program written in C++ that allows you to fetch web objects from HTTP servers.

## Features

- Connects to HTTP servers using sockets
- Sends HTTP GET requests
- Displays the server's response

## Requirements

- Windows operating system
- C++ compiler (e.g., Visual Studio, MinGW)

## Compilation

### Using Visual Studio

1. Open Visual Studio
2. Create a new C++ Console Application
3. Replace the contents of the main.cpp file with the provided code
4. Build the solution

### Using MinGW

```bash
g++ -o http_client main.cpp -lws2_32
```

## Usage

1. Run the compiled executable
2. Enter a URL when prompted (e.g., http://example.com/index.html)
3. The program will display the server's response

## Example

```
Enter the URL (e.g., http://example.com/index.html): http://example.com
Host: example.com
Path: /

Response from server:
HTTP/1.1 200 OK
...
```

## Notes

- This program only works with HTTP (not HTTPS) servers
- Some websites may block or redirect HTTP requests
- Examples of websites that accept HTTP requests: neverssl.com, example.com, httpforever.com
