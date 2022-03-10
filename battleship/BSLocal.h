//
// Created by william on 3/10/22.
//

#ifndef BATTLESHIP_BSLOCAL_H
#define BATTLESHIP_BSLOCAL_H

#include "BSOpponent.h"

class BSLocal : public BSOpponent {
    // board bits
    // 1 = hit
    // 2 = ship
    // 3-end = ship_id
    protected:
        int board[10][10]{};
        int hitBoard[10][10]{};
        int numShips{};
        int numSpacesAlive{};

    protected:
        Status attackedAt(int x, int y) override;
        Status attack(int x, int y) override;
        virtual bool placeShip(Ship ship);
    private:
        int sunkCheck(int x, int y);
    protected:
        void placeRandomShip(int length);
};

#endif //BATTLESHIP_BSLOCAL_H
