//
// Created by william on 4/3/22.
//

#ifndef BATTLESHIP_BSBOTOPPONENT_H
#define BATTLESHIP_BSBOTOPPONENT_H


#include "BSOpponent2.h"
#include "BoardTracker.h"

class BSBotOpponent : public BSOpponent2, public BoardTracker {
    private:
        int lastShotX{};
        int lastShotY{};
        Battleship::Status lastShotResult{Battleship::WAITING};
    public:
        BSBotOpponent() = default;
        bool pollPlaceDone() override;
        void attack(int x, int y) override;
        Battleship::Status ackDone(int& x, int& y) override;
        bool pollAttack(int& x, int& y) override;
        void ackAttack(Battleship::Status status) override;
        void surrender() override {};

    private:
        void placeRandomShip(int length);
};


#endif //BATTLESHIP_BSBOTOPPONENT_H
