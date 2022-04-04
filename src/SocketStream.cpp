//
// Created by william on 4/3/22.
//

#include "SocketStream.h"

SocketStream::SocketStream(const std::string& destination, int port) {
#ifdef _WIN32
    WSAData wsaData;
    WSAStartup(0x0202, &wsaData);
#endif
    this->destination.sin_family = AF_INET;
    thisSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (thisSock < 0) {
        throw std::runtime_error("SocketStream: socket() failed");
    }

    this->destination.sin_port = htons(port);
    this->destination.sin_addr.s_addr = inet_addr(destination.c_str());

    if (bind(thisSock, (struct sockaddr *) &this->destination, sizeof(this->destination)) < 0) {
        throw std::runtime_error("SocketStream: bind() failed");
    }
}

SocketStream::~SocketStream() {
#ifdef _WIN32
    closesocket(thisSock);
    WSACleanup();
#else
    close(thisSock);
#endif
}