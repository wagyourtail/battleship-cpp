//
// Created by william on 3/10/22.
//

#ifndef BATTLESHIP_BSPLAYERGUI_H
#define BATTLESHIP_BSPLAYERGUI_H

#include "BSPlayer.h"

class BSPlayerGui : public BSPlayer {
    public:
        void render(float i, float j, float ts);
        void renderHitBoard(float i, float j, float ts);
        void renderPlace(float i, float j, float ts, int row, int col, bool horizontal);
        bool placeShip(Battleship::Ship ship) override { return BSLocal::placeShip(ship);};
        bool allPlaced() const { return numShips == 5; };
        Battleship::Status attack(int x, int y) override { return BSLocal::attack(x, y); };
        int undoPlace();
        bool isHit(int x, int y) const { return hitBoard[x][y] & 2; };
};

#endif //BATTLESHIP_BSPLAYERGUI_H
