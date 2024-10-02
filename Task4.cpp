#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
using namespace std;
string getHtmlContent(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        return "<html><body><h1>404 Not Found</h1></body></html>";
    }
    return string((istreambuf_iterator<char>(file)),
                        istreambuf_iterator<char>());
}

void handleClient(int client_socket) {
    char buffer[1024] = {0};
    ssize_t bytes_read = read(client_socket, buffer, 1024);
    if (bytes_read < 0) {
        perror("Read failed");
        close(client_socket);
        return;
    }

    string header = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
    string html_content = getHtmlContent("index.html");
    string response = header + html_content;

    send(client_socket, response.c_str(), response.length(), 0);
    close(client_socket);
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    int addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    while (true) {
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        thread(&handleClient, new_socket).detach();
    }

    return 0;
}