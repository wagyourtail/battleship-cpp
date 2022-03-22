//
// Created by william on 3/10/22.
//

#ifndef BATTLESHIP_BSOPPONENT_H
#define BATTLESHIP_BSOPPONENT_H

#include "Battleship.h"

class BSOpponent {
    protected:
        BSOpponent* opponent{};
    public:
        void setOpponent(BSOpponent* opp) {
            opponent = opp;
        };
        virtual ~BSOpponent() = default;
        virtual Battleship::Status attackedAt(int x, int y) = 0;
        virtual Battleship::Status attack(int x, int y) = 0;
        virtual Battleship::Status runTurn() = 0;
        virtual bool setup() = 0;
};

#endif //BATTLESHIP_BSOPPONENT_H
