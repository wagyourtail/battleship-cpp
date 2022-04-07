//
// Created by william on 4/3/22.
//

#ifndef BATTLESHIP_BSBOTOPPONENT_H
#define BATTLESHIP_BSBOTOPPONENT_H


#include "BSOpponent.h"
#include "BoardTracker.h"
#include <random>

class BSBotOpponent : public BSOpponent, public BoardTracker {
    private:
        int lastShotX{};
        int lastShotY{};
        Battleship::Status lastShotResult{Battleship::WAITING};
    public:
        BSBotOpponent() = default;
        bool pollPlaceDone() override;
        void sendPlaceDone() override {};
        void attack(int x, int y) override;
        Battleship::Status ackDone(int& x, int& y) override;
        bool pollAttack(int& x, int& y) override;
        void ackAttack(Battleship::Status status, int x, int y) override;

        void surrender() override {};

        bool goesFirst() override {
            std::random_device rd;
            std::uniform_int_distribution<int> dist(0, 1);
            return dist(rd) == 0;
        }

        bool surrendered() override {
            return false;
        }
    private:
        void placeRandomShip(int length);
};


#endif //BATTLESHIP_BSBOTOPPONENT_H
