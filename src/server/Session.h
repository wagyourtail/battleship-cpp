//
// Created by william on 4/4/22.
//

#ifndef BATTLESHIP_SERVER_SESSION_H
#define BATTLESHIP_SERVER_SESSION_H


#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <cstdio>
#include <unordered_map>
#include <string>
#include <memory>
#include <thread>
#include <utility>
#include "shared/SocketConnection.h"

class Session : public std::enable_shared_from_this<Session> {

        static std::unordered_map<std::string, std::shared_ptr<Session>> sessions;

        std::string session_id;

        std::thread host_read_thread{};
        std::thread client_read_thread{};

        std::shared_ptr<SocketConnection> host_connection{nullptr};
        std::shared_ptr<SocketConnection> client_connection{nullptr};

        bool alive{true};

    public:
        Session(std::string session_id, int hostFd) :
                session_id(std::move(session_id)), host_connection(std::make_shared<SocketConnection>(hostFd)) {}

        ~Session() {
//            std::cout << "Session destructor" << std::endl;
            alive = false;
            //detatch to not kill the main thread, they should stop themselves shortly anyway...
            host_read_thread.detach();
            client_read_thread.detach();
        }

        static void connect(int unknownFd);
    private:
        void start(int clientFd);
        static void hostRead(std::shared_ptr<Session> session);
        static void clientRead(std::shared_ptr<Session> session);
};

#endif //BATTLESHIP_SERVER_SESSION_H
