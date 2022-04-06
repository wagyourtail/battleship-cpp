//
// Created by william on 4/4/22.
//

#ifndef BATTLESHIP_SERVER_SESSION_H
#define BATTLESHIP_SERVER_SESSION_H


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdio>
#include <unordered_map>
#include <string>
#include <memory>
#include <thread>
#include <utility>
#include "shared/SocketConnection.h"

class Session {

    static std::unordered_map<std::string, Session> sessions;

    std::string session_id;

    std::thread host_read_thread{};
    std::thread client_read_thread{};

    std::unique_ptr<SocketConnection> host_connection{nullptr};
    std::unique_ptr<SocketConnection> client_connection{nullptr};

    bool alive{true};

    public:
        Session(std::string session_id, int hostFd) : session_id(std::move(session_id)), host_connection(std::make_unique<SocketConnection>(hostFd)) {}
        void start(int clientFd);
        static void connect(int unknownFd);
        void hostRead();
        void clientRead();
};

#endif //BATTLESHIP_SERVER_SESSION_H
