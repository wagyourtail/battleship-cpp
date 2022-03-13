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
        bool placeShip(Battleship::Ship ship) override { return BSLocal::placeShip(ship);};
};

#endif //BATTLESHIP_BSPLAYERGUI_H
