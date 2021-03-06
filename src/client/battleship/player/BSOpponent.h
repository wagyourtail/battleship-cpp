//
// Created by ruwag on 3/30/2022.
//

#ifndef BATTLESHIP_BSOPPONENT2_H
#define BATTLESHIP_BSOPPONENT2_H


#include <memory>
#include "client/battleship/Battleship.h"

class BSOpponent {
    public:
        // <-
        virtual bool pollPlaceDone() = 0;

        // ->
        virtual void sendPlaceDone() = 0;

        // send attack to opponent
        // ->
        virtual void attack(int x, int y) = 0;
        // poll opponent, returns status & cords of attack back, or nullptr if still waiting
        // <-
        virtual Battleship::Status ackDone(int& x, int& y) = 0;

        // poll opponent, returns status & cords of attack back, or false if still waiting
        // <-
        virtual bool pollAttack(int& x, int& y) = 0;
        // send acknowledgement of attack back to opponent with status
        // ->
        virtual void ackAttack(Battleship::Status status, int x, int y) = 0;

        // ->
        virtual void surrender() = 0;

        virtual bool goesFirst() = 0;

        virtual bool surrendered() = 0;
};


#endif //BATTLESHIP_BSOPPONENT2_H
