//
// Created by william on 3/25/22.
//

#ifndef BATTLESHIP_GAMESTATEMACHINE_H
#define BATTLESHIP_GAMESTATEMACHINE_H

#include <memory>
#include "Battleship.h"
#include "battleship/player2/BSOpponent2.h"
#include "battleship/player2/BsPlayer2.h"

class GameStateMachine {
    public:
        enum GameStates {
            PLACE_SHIPS,
            WAIT_FOR_OPPONENT_PLACE_SHIPS,
            PLAYER_TURN,
            WAIT_FOR_OPPONENT_ACK,
            ACK_OPPONENT_TURN,
            GAME_OVER
        };

    protected:
        GameStates gameState = PLACE_SHIPS;
        std::shared_ptr<BSPlayer2> player;
        std::shared_ptr<BSOpponent2> opponent;

    public:
        virtual void poll();
        virtual void transition(const std::shared_ptr<Battleship::Status>& status, int x, int y);
        GameStates getGameState() const { return gameState; }
};


#endif //BATTLESHIP_GAMESTATEMACHINE_H
