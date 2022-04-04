//
// Created by william on 4/3/22.
//

#ifndef BATTLESHIP_SOCKETSTREAM_H
#define BATTLESHIP_SOCKETSTREAM_H

#include <iostream>
#include <string>

#ifdef _WIN32
#include <winsock.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#include "BasePacket.h"


class SocketStream {
    protected:
        int thisSock;
        struct sockaddr_in destination;
    public:
        SocketStream(const std::string& destination, int port);
        ~SocketStream();
        friend SocketStream& operator<<(SocketStream& stream, const BasePacket& message);
        friend SocketStream& operator>>(SocketStream& stream, BasePacket& message);
};


#endif //BATTLESHIP_SOCKETSTREAM_H
