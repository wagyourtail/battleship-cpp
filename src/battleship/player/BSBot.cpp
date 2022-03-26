//
// Created by william on 3/10/22.
//

#include "BSBot.h"
#include "battleship/Battleship.h"
#include <random>

Battleship::Status BSBot::runTurn() {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 9);
    int x, y;
    do {
        x = dist(rd);
        y = dist(rd);
    } while (hitBoard[x][y] & 1);
    return attack(x, y);
}