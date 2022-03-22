//
// Created by william on 3/10/22.
//

#ifndef BATTLESHIP_NOGUIRUNNER_H
#define BATTLESHIP_NOGUIRUNNER_H

#include "BSPlayer.h"
#include "BSOpponent.h"

class NoGuiRunner {
    private:
        BSPlayer* player;
        BSOpponent* opponent;
    public:
        NoGuiRunner(BSPlayer* player, BSOpponent* opponent) : player(player), opponent(opponent) {
            player->setOpponent(opponent);
            opponent->setOpponent(player);
        }
        virtual void runGame();
};

#endif //BATTLESHIP_NOGUIRUNNER_H
