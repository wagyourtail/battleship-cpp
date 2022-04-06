//
// Created by william on 4/5/22.
//

#ifndef BATTLESHIP_SERVER_SOCKETCONNECTION_H
#define BATTLESHIP_SERVER_SOCKETCONNECTION_H

#include <unistd.h>
#include <iostream>
#include <string>

class SocketConnection {
        int socket_fd;
    public:
        explicit SocketConnection(int socket_fd) : socket_fd(socket_fd) {}
        ~SocketConnection() {
            close(socket_fd);
        }
        int get_socket_fd() const { return socket_fd; }
        friend SocketConnection& operator<<(SocketConnection& socketConnection, std::string const& message);
        friend SocketConnection& operator>>(SocketConnection& socketConnection, std::string& message);
};


#endif //BATTLESHIP_SERVER_SOCKETCONNECTION_H
