//
// Created by william on 4/2/22.
//

#include "BoardTracker.h"

bool BoardTracker::placeShip(int x, int y, int length, bool horizontal) {
    if (frozen) {
        throw std::runtime_error("BoardTracker is frozen");
    }
    ships[shipsPlaced] = {x, y, length, horizontal};
    int sid = ++shipsPlaced;
    sid <<= 2;
    sid |= 2;
    if (horizontal) {
        for (int i = x; i < x + length; ++i) {
            if (board[i][y] >> 2 != 0 || i > 9 || i < 0) {
                --shipsPlaced;
                return false;
            }
        }
        for (int i = x; i < x + length; ++i) {
            board[i][y] = sid;
        }
    } else {
        for (int i = y; i < y + length; ++i) {
            if (board[x][i] >> 2 != 0 || i > 9 || i < 0) {
                --shipsPlaced;
                return false;
            }
        }
        for (int i = y; i < y + length; ++i) {
            board[x][i] = sid;
        }
    }
    shipTilesAlive += length;
    return true;
}

void BoardTracker::attack(Battleship::Status status, int x, int y) {
    switch (status) {
        case Battleship::HIT:
        case Battleship::SUNK_2:
        case Battleship::SUNK_3:
        case Battleship::SUNK_4:
        case Battleship::SUNK_5:
        case Battleship::GAME_END:
            attackBoard[x][y] |= 2;
        case Battleship::MISS:
            attackBoard[x][y] |= 1;
        case Battleship::ERROR:
        case Battleship::WAITING:
            break;
    }
}

Battleship::Status BoardTracker::attacked(int x, int y) {
    if (board[x][y] & 1) {
        return Battleship::ERROR;
    }
    board[x][y] |= 1;
    if (board[x][y] & 2) {
        --shipTilesAlive;
        if (shipTilesAlive == 0) {
            return Battleship::GAME_END;
        }
        // todo, return sunk status
        return Battleship::HIT;
    }
    return Battleship::MISS;
}

int BoardTracker::undoPlace() {
    if (frozen) {
        throw std::runtime_error("BoardTracker is frozen");
    }
    if (shipsPlaced == 0) {
        return 0;
    }

    --shipsPlaced;
    Battleship::Ship ship = ships[shipsPlaced];
    if (ship.horizontal) {
        for (int i = ship.x; i < ship.x + ship.length; ++i) {
            board[i][ship.y] = 0;
        }
    } else {
        for (int i = ship.y; i < ship.y + ship.length; ++i) {
            board[ship.x][i] = 0;
        }
    }
    return shipsPlaced;
}
