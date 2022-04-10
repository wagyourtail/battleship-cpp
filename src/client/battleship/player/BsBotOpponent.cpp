//
// Created by william on 4/3/22.
//

#include <random>
#include "BsBotOpponent.h"

bool BSBotOpponent::pollPlaceDone() {
    for (auto& i: Battleship::SHIP_LENGTHS) {
        placeRandomShip(i);
    }

    freeze();
    return true;
}

void BSBotOpponent::placeRandomShip(int length) {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 9);
    int x, y;
    bool horizontal;
    do {
        x = dist(rd);
        y = dist(rd);
        horizontal = dist(rd) % 2;
    } while (!placeShip(x, y, length, horizontal));
}

void BSBotOpponent::attack(int x, int y) {
    if (lastShotResult != Battleship::Status::WAITING) {
        throw std::runtime_error("prev attack not polled!");
    }
    if (x < 0 || x > 9 || y < 0 || y > 9) {
        lastShotResult = Battleship::Status::BS_ERROR;
    } else {
        lastShotResult = attacked(x, y);
        lastShotX = x;
        lastShotY = y;
    }
}

Battleship::Status BSBotOpponent::ackDone(int& x, int& y) {
    Battleship::Status result = lastShotResult;
    lastShotResult = Battleship::Status::WAITING;
    x = lastShotX;
    y = lastShotY;
    return result;
}

bool BSBotOpponent::pollAttack(int& x, int& y) {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 9);
    do {
        x = dist(rd);
        y = dist(rd);
    } while (attackBoard[x][y] & 1);
    lastShotX = x;
    lastShotY = y;
    return true;
}

void BSBotOpponent::ackAttack(Battleship::Status status, int x, int y) {
    BoardTracker::attack(status, x, y);
}
