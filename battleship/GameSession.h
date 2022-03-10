//
// Created by william on 3/10/22.
//

#ifndef BATTLESHIP_GAMESESSION_H
#define BATTLESHIP_GAMESESSION_H

#include "BSPlayerGui.h"
#include "BSOpponent.h"

class GameSession {
    public:
        BSPlayerGui *player;
        BSOpponent *opponent;
        GameSession(BSPlayerGui *player, BSOpponent *opponent) : player(player), opponent(opponent) {
            player->setOpponent(opponent);
            opponent->setOpponent(player);
        }
        ~GameSession() {
            delete player;
            delete opponent;
        }
};

#endif //BATTLESHIP_GAMESESSION_H
