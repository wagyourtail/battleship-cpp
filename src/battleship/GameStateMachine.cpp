//
// Created by william on 3/25/22.
//

#include "GameStateMachine.h"

void GameStateMachine::poll()  {
    switch (gameState) {
        case PLACE_SHIPS:
            break;
        case WAIT_FOR_OPPONENT_PLACE_SHIPS:
            if (opponent->pollPlaceDone()) {
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
            if (opponent->pollAttack(x, y)) {
                transition(nullptr, x, y);
            }
            break;
        }
        case GAME_OVER:
            break;
    }
}

void GameStateMachine::transition(const std::shared_ptr<Battleship::Status>& status, int x, int y) {
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
            if (*status == Battleship::ERROR) {
                gameState = PLAYER_TURN;
            } else if (*status == Battleship::GAME_END) {
                gameState = GAME_OVER;
            } else {
                player->hitboard(status, x, y);
                gameState = ACK_OPPONENT_TURN;
            }
            break;
        case ACK_OPPONENT_TURN: {
            Battleship::Status hitStatus = player->attacked(x, y);
            if (hitStatus != Battleship::ERROR) {
                gameState = PLAYER_TURN;
            }
            break;
        }
        case GAME_OVER:
            break;
    }
}