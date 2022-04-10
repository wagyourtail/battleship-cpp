//
// Created by william on 4/4/22.
//

#ifndef BATTLESHIP_SERVER_REMOTEOPPONENT_H
#define BATTLESHIP_SERVER_REMOTEOPPONENT_H


#include "BSOpponent.h"
#include "shared/SocketConnection.h"
#include <unistd.h>
#include <thread>
#include <mutex>

class RemoteOpponent : public BSOpponent, std::enable_shared_from_this<RemoteOpponent> {
    public:
        std::shared_ptr<SocketConnection> connection;
        std::thread connectionThread{};
        bool gf{};

    protected:
        std::mutex mtx{};
        bool placeDone{false};
        int lastX{-1};
        int lastY{-1};
        Battleship::Status lastStatus{Battleship::Status::WAITING};

    public:
        explicit RemoteOpponent(int socket_fd) : connection(std::make_shared<SocketConnection>(socket_fd)) {}

        ~RemoteOpponent() {
            //if I didn't mess anything up, this should be safe
            connectionThread.detach();
        }

        void sendPlaceDone() override;
        bool pollPlaceDone() override;
        void attack(int x, int y) override;
        Battleship::Status ackDone(int& x, int& y) override;
        bool pollAttack(int& x, int& y) override;
        void ackAttack(Battleship::Status status, int x, int y) override;
        void surrender() override;

        bool goesFirst() override { return gf; }

        void beginMainGameReadTask();

        bool surrendered() override {
            return lastStatus == Battleship::Status::GAME_END;
        }
};

#endif //BATTLESHIP_SERVER_REMOTEOPPONENT_H
