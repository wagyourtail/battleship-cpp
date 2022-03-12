//
// Created by william on 3/10/22.
//

#ifndef BATTLESHIP_GAMESESSION_H
#define BATTLESHIP_GAMESESSION_H

#include "BSPlayerGui.h"
#include "BSOpponent.h"

enum GameState {
    PLACE_SHIPS,
    PLAYER_TURN,
    OPPONENT_TURN,
    GAME_OVER
};

class GameSession {
    public:
        BSPlayerGui *player;
        BSOpponent *opponent;
    private:
        GameState state{PLACE_SHIPS};
    public:
        GameSession(BSPlayerGui *player, BSOpponent *opponent) : player(player), opponent(opponent) {
            player->setOpponent(opponent);
            opponent->setOpponent(player);
        }
        ~GameSession() {
            delete player;
            delete opponent;
        }
        GameState getState() {
            return state;
        }
};

#endif //BATTLESHIP_GAMESESSION_H
