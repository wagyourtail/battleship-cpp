//
// Created by william on 3/10/22.
//

#ifndef BATTLESHIP_GAMESESSION_H
#define BATTLESHIP_GAMESESSION_H

#include <random>
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
        BSPlayerGui* player;
        BSOpponent* opponent;
    protected:
        GameState state{PLACE_SHIPS};
        Battleship::Status stateChangeStatus{Battleship::Status::MISS};
    public:
        GameSession(BSPlayerGui* player, BSOpponent* opponent) : player(player), opponent(opponent) {
            player->setOpponent(opponent);
            opponent->setOpponent(player);
        }

        ~GameSession() {
            delete player;
            delete opponent;
        }

        GameState getState() const {
            return state;
        }

        void attack(int col, int row) {
            stateChangeStatus = player->attack(col, row);
            if (stateChangeStatus == Battleship::GAME_END) {
                state = GAME_OVER;
            } else if (stateChangeStatus != Battleship::ERROR) {
                state = OPPONENT_TURN;
            }

        }

        void finishPlace() {
            if (state == PLACE_SHIPS) {
                std::random_device rd;
                std::uniform_int_distribution<int> dist(0, 1);
                if (dist(rd)) {
                    state = PLAYER_TURN;
                } else {
                    state = OPPONENT_TURN;
                }
            }
        }

        bool pollSetup() const {
            return opponent->setup();
        }

        void pollOpponent() {
            if (state == OPPONENT_TURN) {
                stateChangeStatus = opponent->runTurn();
                if (stateChangeStatus == Battleship::GAME_END) {
                    state = GAME_OVER;
                } else if (stateChangeStatus != Battleship::ERROR) {
                    state = PLAYER_TURN;
                }
            }
        }

        void surrender() {
            state = GAME_OVER;
            //TODO: add surrender logic to notify opponent
        }
};

#endif //BATTLESHIP_GAMESESSION_H
