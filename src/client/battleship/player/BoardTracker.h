//
// Created by william on 4/2/22.
//

#ifndef BATTLESHIP_BOARDTRACKER_H
#define BATTLESHIP_BOARDTRACKER_H


#include "client/battleship/Battleship.h"

class BoardTracker {
    protected:
        int board[10][10]{};
        int attackBoard[10][10]{};
        int shipTilesAlive{0};
        Battleship::Ship ships[5]{};
        int shipsPlaced{0};
    private:
        bool frozen{false};
    public:
        void attack(Battleship::Status status, int x, int y);
        bool placeShip(int x, int y, int length, bool horizontal);

        bool attackBoardHit(int x, int y) const { return attackBoard[x][y] & 2; }

        int undoPlace();

        void freeze() { frozen = true; }

        bool isFrozen() const { return frozen; }

        Battleship::Status attacked(int x, int y);

        bool isLost() const { return shipTilesAlive == 0; }
};


#endif //BATTLESHIP_BOARDTRACKER_H
