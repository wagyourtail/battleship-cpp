//
// Created by william on 4/5/22.
//

#include "SocketConnection.h"
#include <cstring>

// thx
// https://www.techpowerup.com/forums/threads/c-c-sockets-faq-and-how-to-win-linux.56901/

template<class T, class U>
inline auto min(T a, U b) -> decltype(a + b) {
    return a < b ? a : b;
}

SocketConnection& operator <<(SocketConnection& socket, const std::string& str) {
    int status = write(socket.socket_fd, str.c_str(), str.size() + 1);
    socket.fail_flag = status;
    return socket;
}

SocketConnection& operator >>(SocketConnection& socket, std::string& str) {
    char buffer[1024];
    int status = read(socket.socket_fd, buffer, 1024);
    socket.fail_flag = status;
    if (status > 0) str = std::string(buffer, min(strlen(buffer), 1024));
    return socket;
}