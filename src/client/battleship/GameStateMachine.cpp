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
                transition(Battleship::WAITING, 0, 0);
            }
            break;
        case PLAYER_TURN:
            if (opponent->surrendered()) {
                gameState = GAME_OVER;
            }
            break;
        case WAIT_FOR_OPPONENT_ACK: {
            int x, y;
            Battleship::Status ack = opponent->ackDone(x, y);
            if (ack != Battleship::WAITING) {
                transition(ack, x, y);
            }
            break;
        }
        case ACK_OPPONENT_TURN: {
            int x, y;
            if (opponent->surrendered()) {
                gameState = GAME_OVER;
            }
            if (opponent->pollAttack(x, y)) {
                transition(Battleship::WAITING, x, y);
            }
            break;
        }
        case GAME_OVER:
            break;
    }
}

void GameStateMachine::transition(Battleship::Status status, int x, int y) {
    switch (gameState) {
        case PLACE_SHIPS:
            opponent->sendPlaceDone();
            gameState = WAIT_FOR_OPPONENT_PLACE_SHIPS;
            break;
        case WAIT_FOR_OPPONENT_PLACE_SHIPS:
            gameState = opponent->goesFirst() ? ACK_OPPONENT_TURN : PLAYER_TURN;
            break;
        case PLAYER_TURN:
            opponent->attack(x, y);
            gameState = WAIT_FOR_OPPONENT_ACK;
            break;
        case WAIT_FOR_OPPONENT_ACK:
            if (status == Battleship::ERROR) {
                gameState = PLAYER_TURN;
            } else if (status == Battleship::GAME_END) {
                gameState = GAME_OVER;
            } else {
                player->attack(status, x, y);
                gameState = ACK_OPPONENT_TURN;
            }
            break;
        case ACK_OPPONENT_TURN: {
            Battleship::Status hitStatus = player->attacked(x, y);
            if (hitStatus == Battleship::GAME_END) {
                gameState = GAME_OVER;
            } else if (hitStatus != Battleship::ERROR) {
                opponent->ackAttack(hitStatus, x, y);
                gameState = PLAYER_TURN;
            } else {
                opponent->ackAttack(hitStatus, x, y);
            }
            break;
        }
        case GAME_OVER:
            break;
    }
}