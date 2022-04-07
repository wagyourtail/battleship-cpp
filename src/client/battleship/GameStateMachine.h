//
// Created by william on 3/25/22.
//

#ifndef BATTLESHIP_GAMESTATEMACHINE_H
#define BATTLESHIP_GAMESTATEMACHINE_H

#include <memory>
#include <utility>
#include "Battleship.h"
#include "client/battleship/player/BSOpponent.h"
#include "client/battleship/player/BsPlayer.h"

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
        std::shared_ptr<BSPlayer> player;
        std::shared_ptr<BSOpponent> opponent;

    public:
        GameStateMachine(std::shared_ptr<BSPlayer> player, std::shared_ptr<BSOpponent> opponent) :
                player(std::move(player)), opponent(std::move(opponent)) {}

        virtual void poll();
        virtual void transition(Battleship::Status status, int x, int y);

        GameStates getGameState() const { return gameState; }

        std::shared_ptr<BSPlayer> getPlayer() const { return player; }

        std::shared_ptr<BSOpponent> getOpponent() const { return opponent; }
};


#endif //BATTLESHIP_GAMESTATEMACHINE_H
