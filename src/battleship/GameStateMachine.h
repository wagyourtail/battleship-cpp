//
// Created by william on 3/25/22.
//

#ifndef BATTLESHIP_GAMESTATEMACHINE_H
#define BATTLESHIP_GAMESTATEMACHINE_H

#include <memory>
#include "Battleship.h"
#include "battleship/player/BSPlayer.h"

class GameStateMachine {
    protected:
        enum GameStates {
            PLACE_SHIPS,
            WAIT_FOR_OPPONENT_PLACE_SHIPS,
            PLAYER_TURN,
            WAIT_FOR_OPPONENT_ACK,
            ACK_OPPONENT_TURN,
            GAME_OVER
        };

        GameStates gameState = PLACE_SHIPS;
        std::shared_ptr<BSPlayer> player;
        std::shared_ptr<BSOpponent> opponent;

    public:
        virtual void poll() {
            switch (gameState) {
                case PLACE_SHIPS:
                    break;
                case WAIT_FOR_OPPONENT_PLACE_SHIPS:
                    if (opponent->isPlaceDone()) {
                        transition(nullptr, 0, 0);
                    }
                    break;
                case PLAYER_TURN:
                    break;
                case WAIT_FOR_OPPONENT_ACK: {
                    int x, y;
                    std::shared_ptr<Battleship::Status> ack = opponent->ackDone(x, y);
                    if (ack != nullptr) {
                        transition(ack, x, y);
                    }
                    break;
                }
                case ACK_OPPONENT_TURN: {
                    int x, y;
                    std::shared_ptr<Battleship::Status> ack = opponent->pollTurn(x, y);
                    if (ack != nullptr) {
                        transition(ack, x, y);
                    }
                    break;
                }
                case GAME_OVER:
                    break;
            }
        }
        virtual void transition(std::shared_ptr<Battleship::Status> status, int x, int y) {
            switch (gameState) {
                case PLACE_SHIPS:
                    gameState = WAIT_FOR_OPPONENT_PLACE_SHIPS;
                    break;
                case WAIT_FOR_OPPONENT_PLACE_SHIPS:
                    gameState = PLAYER_TURN;
                    break;
                case PLAYER_TURN:
                    gameState = WAIT_FOR_OPPONENT_ACK;
                    break;
                case WAIT_FOR_OPPONENT_ACK:
                    gameState = ACK_OPPONENT_TURN;
                    break;
                case ACK_OPPONENT_TURN:
                    gameState = PLAYER_TURN;
                    break;
                case GAME_OVER:
                    break;
            }
        }
};


#endif //BATTLESHIP_GAMESTATEMACHINE_H
