//
// Created by william on 3/10/22.
//

#ifndef BATTLESHIP_BSBOT_H
#define BATTLESHIP_BSBOT_H

#include "BSLocal.h"
#include "Battleship.h"

class BSBot : public BSLocal {
    public:
        void setup() override {
            for (auto & i : Battleship::SHIP_LENGTHS) {
                placeRandomShip(i);
            }
        }
        Battleship::Status runTurn() override;
};

#endif //BATTLESHIP_BSBOT_H
