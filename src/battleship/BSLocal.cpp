//
// Created by william on 3/10/22.
//

#include "BSLocal.h"
#include "Battleship.h"
#include <random>

using namespace Battleship;

Battleship::Status BSLocal::attackedAt(int x, int y) {
    // space already hit
    if (board[x][y] & 1) {
        return ERROR;
    }

    board[x][y] |= 1;

    // hit
    if (board[x][y] & 2) {
        int sc = sunkCheck(x, y);
        --numSpacesAlive;

        if (numSpacesAlive == 0) {
            return GAME_END;
        }

        if (sc == 0) return HIT;

        switch (sc) {
            case 2:
                return SUNK_2;
            case 3:
                return SUNK_3;
            case 4:
                return SUNK_4;
            case 5:
                return SUNK_5;
            default:
                return ERROR;
        }
    }
    return MISS;
}

int BSLocal::sunkCheck(int x, int y) {
    int shipid = board[x][y] >> 2;

    // no ship so always false
    if (shipid == 0) {
        return 0;
    }

    int l = 0;
    bool horizontal = false;
    if (x > 0 && board[x - 1][y] >> 2 == shipid) {
        // go to left end
        while (board[--x][y] >> 2 == shipid) {}
        horizontal = true;
    } else if (x < 9 && board[x + 1][y] >> 2 == shipid) {
        // already at left end
        --x;
        horizontal = true;
    } else if (y > 0 && board[x][y - 1] >> 2 == shipid) {
        // go to top
        while (board[x][--y] >> 2 == shipid) {}
    } else if (y < 9 && board[x][y + 1] >> 2 == shipid) {
        // already at top
        --y;
    } else {
        return 0;
    }

    int boardspot;
    if (horizontal) {
        // go to right end
        while ((boardspot = board[++x][y]) >> 2 == shipid) {
            ++l;
            if (!(boardspot & 1)) {
                return 0;
            }
        }
    } else {
        // go to bottom
        while ((boardspot = board[x][++y]) >> 2 == shipid) {
            ++l;
            if (!(boardspot & 1)) {
                return 0;
            }
        }
    }
    return l - 1;
}

Battleship::Status BSLocal::attack(int x, int y) {
    if (hitBoard[x][y] & 1) {
        return ERROR;
    }
    Battleship::Status status = opponent->attackedAt(x, y);
    switch (status) {
        case ERROR:
            return ERROR;
        case SUNK_2:
        case SUNK_3:
        case SUNK_4:
        case SUNK_5:
        case HIT:
            hitBoard[x][y] |= 3;
            return status;
        case MISS:
            hitBoard[x][y] |= 1;
            return MISS;
        case GAME_END:
            return GAME_END;
    }
    return ERROR;
}

bool BSLocal::placeShip(Battleship::Ship ship) {
    ships[numShips] = ship;
    int sid = ++numShips;
    sid <<= 2;
    sid |= 2;
    if (ship.horizontal) {
        for (int i = ship.x; i < ship.x + ship.length; ++i) {
            if (board[i][ship.y] >> 2 != 0 || i > 9 || i < 0) {
                --numShips;
                return false;
            }
        }
        for (int i = ship.x; i < ship.x + ship.length; ++i) {
            board[i][ship.y] = sid;
        }
    } else {
        for (int i = ship.y; i < ship.y + ship.length; ++i) {
            if (board[ship.x][i] >> 2 != 0 || i > 9 || i < 0) {
                --numShips;
                return false;
            }
        }
        for (int i = ship.y; i < ship.y + ship.length; ++i) {
            board[ship.x][i] = sid;
        }
    }
    numSpacesAlive += ship.length;
    return true;
}

void BSLocal::placeRandomShip(int length) {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 9);
    int x, y;
    bool horizontal;
    do {
        x = dist(rd);
        y = dist(rd);
        horizontal = dist(rd) % 2;
    } while (!placeShip({x, y, length, horizontal}));
}