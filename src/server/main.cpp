//
// Created by william on 4/3/22.
//
#ifdef __LINUX
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#ifdef __WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#endif
#include <cstdio>
#include "Session.h"

// thx
// https://www.techpowerup.com/forums/threads/c-c-sockets-faq-and-how-to-win-linux.56901/

int main(int argc, char* argv[]) {
#ifdef __WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    // socket
    int server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_fd == -1) {
        perror("socket");
        return 1;
    }
    // bind
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5549);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        return 1;
    }
    // listen
    while (true) {
        if (listen(server_fd, 5) == -1) {
            perror("listen");
            return 1;
        }
        // accept
        sockaddr_in client_addr{};
        socklen_t client_addr_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr*) &client_addr, &client_addr_len);
        Session::connect(client_fd);
    }
}