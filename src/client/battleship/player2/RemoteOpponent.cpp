//
// Created by william on 4/4/22.
//

#include <sstream>
#include "RemoteOpponent.h"

bool RemoteOpponent::pollPlaceDone() {
    return placeDone;
}

void RemoteOpponent::attack(int x, int y) {
    *connection << ("attack " + std::to_string(x) + " " + std::to_string(y));
}

Battleship::Status RemoteOpponent::ackDone(int& x, int& y) {
    mtx.lock();
    Battleship::Status status = lastStatus;
    x = lastX;
    y = lastY;
    lastStatus = Battleship::WAITING;
    lastX = -1;
    lastY = -1;
    mtx.unlock();
    return status;
}

bool RemoteOpponent::pollAttack(int& x, int& y) {
    mtx.lock();
    x = lastX;
    y = lastY;
    lastX = -1;
    lastY = -1;
    mtx.unlock();
    return x > 0;
}

void RemoteOpponent::ackAttack(Battleship::Status status, int x, int y) {
    *connection << ("ackAttack " + std::to_string(status) + " " + std::to_string(x) + " " + std::to_string(y));
}

void RemoteOpponent::surrender() {
    *connection << "gameover";
}

void RemoteOpponent::beginMainGameReadTask() {
    std::string message;
    try {
        while (true) {
            message = "";
            *connection >> message;
            if (connection->fail()) {
                std::cout << "Connection to opponent lost" << std::endl;
                lastStatus = Battleship::GAME_END;
                break;
            }
            std::stringstream ss(message);
            std::string command;
            ss >> command;
//            std::cout << command << std::endl;
            if (command == "attack") {
                mtx.lock();
                ss >> lastX;
                ss >> lastY;
                mtx.unlock();
            } else if (command == "ackAttack") {
                mtx.lock();
                int x;
                ss >> x;
                lastStatus = (Battleship::Status) x;
                ss >> lastX;
                ss >> lastY;
                mtx.unlock();
            } else if (command == "placeDone") {
                mtx.lock();
                placeDone = true;
                mtx.unlock();
            } else if (command == "gameover") {
                lastStatus = Battleship::GAME_END;
                break;
            }

        }
    } catch (...) {}

    std::cout << "disconnected" << std::endl;
}

void RemoteOpponent::sendPlaceDone() {
    *connection << "placeDone";
}

