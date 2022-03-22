//
// Created by william on 3/10/22.
//

#ifndef BATTLESHIP_BSPLAYER_H
#define BATTLESHIP_BSPLAYER_H

#include "BSLocal.h"
#include "Battleship.h"
#include <iostream>

class BSPlayer : public BSLocal {
    public:
        bool setup() override {
            for (auto & ship : Battleship::SHIP_LENGTHS) {
                render();
                promptShipPlacement(ship);
            }
            return true;
        }
        Battleship::Status attackedAt(int x, int y) override {
            char xchar = x + 'a';
            std::cout << "opponent attacked at " << xchar << y + 1 << "!" << std::endl;
            return BSLocal::attackedAt(x, y);
        };
        virtual void render();
        virtual void renderHitBoard();
        void promptShipPlacement(int length);
        Battleship::Status runTurn() override;
};

#endif //BATTLESHIP_BSPLAYER_H
