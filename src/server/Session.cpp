//
// Created by william on 4/4/22.
//

#include <iostream>
#include <thread>
#include <random>
#include "Session.h"

std::unordered_map<std::string, std::shared_ptr<Session>> Session::sessions{};

void Session::start(int clientFd) {
    if (this->client_connection != nullptr) {
        std::string pkt = "err, already started";
        send(clientFd, pkt.c_str(), pkt.length(), 0);
        close(clientFd);
        return;
    }
    this->client_connection = std::make_shared<SocketConnection>(clientFd);

    // roll who goes first
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 1);
    bool host_start = dist(rd);

    *host_connection << (host_start ? "s1" : "s0");
    *client_connection << (host_start ? "s0" : "s1");

    host_read_thread = std::thread(&Session::hostRead, shared_from_this());
    client_read_thread = std::thread(&Session::clientRead, shared_from_this());

//    std::cout << "Session::start " << session_id << std::endl;
}

void Session::connect(int unknownFd) {
    std::thread t([=]() {
        char buffer[1024];
        ssize_t n = read(unknownFd, buffer, sizeof(buffer));
        if (n < 0) {
            perror("read");
            exit(1);
        }
        if (buffer[0] == 'h') {
//            std::cout << "new host" << std::endl;
            std::random_device rd;
            std::uniform_int_distribution<int> dist(0, 35);
            std::string session_id;
            do {
                session_id = "";
                for (int i = 0; i < 5; ++i) {
                    char c = dist(rd);
                    if (c < 10) {
                        c += '0';
                    } else {
                        c += 'A' - 10;
                    }
                    session_id += c;
                }
            } while (sessions.find(session_id) != sessions.end());
            std::string session_pkt = "s" + session_id;
            write(unknownFd, session_pkt.c_str(), session_pkt.size());

            sessions.insert(std::make_pair(session_id, std::make_shared<Session>(session_id, unknownFd)));

            // kill if no client connects after 1 minute
            std::this_thread::sleep_for(std::chrono::seconds(60));
            int error_code;
            socklen_t error_code_size = sizeof(error_code);
            getsockopt(unknownFd, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);
//            std::cout << "error code: " << error_code << std::endl;

            if (error_code != 0) {
                auto it = sessions.find(session_id);
                if (it != sessions.end()) {
                    if (it->second->client_connection == nullptr) {
                        sessions.erase(it);
                    } else {
                        return;
                    }
                }
                close(unknownFd);
            }

        } else if (buffer[0] == 'j') {
            std::cout << "new client ";
            std::string session_id(buffer + 1, buffer + 6);
            std::cout << "session id: " << session_id << std::endl;

            auto it = sessions.find(session_id);
            if (it == sessions.end()) {
                std::string error_pkt = "e" + session_id;
                write(unknownFd, error_pkt.c_str(), error_pkt.size());
                close(unknownFd);
            } else {
                it->second->start(unknownFd);
            }
        } else {
            close(unknownFd);
        }
    });
    t.detach();
}


void Session::hostRead(std::shared_ptr<Session> session) {
    try {
        while (session->alive) {
//            std::cout << "host read" << std::endl;
            std::string msg;
            *session->client_connection >> msg;
            if (!session->alive) {
                break;
            }
            if (session->client_connection->fail()) {
                session->alive = false;
                session->host_connection = nullptr;
                sessions.erase(session->session_id);
                break;
            }
//            std::cout << "session id: " << session->session_id << " <<" << msg << std::endl;
            *session->host_connection << msg;
            if (msg == "gameover") {
                session->alive = false;
                session->host_connection = nullptr;
                sessions.erase(session->session_id);
                break;
            }
        }
        session->host_connection = nullptr;
    } catch (...) {}

//    std::cout << "host read end" << std::endl;
}

void Session::clientRead(std::shared_ptr<Session> session) {
    try {
        while (session->alive) {
//            std::cout << "client read" << std::endl;
            std::string msg;
            *session->host_connection >> msg;
            if (!session->alive) {
                break;
            }
            if (session->host_connection->fail()) {
                session->alive = false;
                session->client_connection = nullptr;
                sessions.erase(session->session_id);
                break;
            }
//            std::cout << "session id: " << session->session_id << " >>" << msg << std::endl;
            *session->client_connection << msg;
            if (msg == "gameover") {
                session->alive = false;
                session->client_connection = nullptr;
                sessions.erase(session->session_id);
                break;
            }
        }
        session->host_connection = nullptr;
    } catch (...) {}

//    std::cout << "client read end" << std::endl;
}