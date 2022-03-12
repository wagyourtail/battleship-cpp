//
// Created by william on 3/10/22.
//

#include "NoGuiRunner.h"
#include <iostream>
#include <random>

using namespace Battleship;

void NoGuiRunner::runGame() {
    std::cout << "Welcome to Battleship!" << std::endl;
    std::cout << "Place your ships!" << std::endl;
    player->setup();
    opponent->setup();
    std::cout << "Your board:" << std::endl;
    player->render();
    std::cout << "prepare to battle!" << std::endl;
    // select starting player
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 1);
    int start = dist(rd);
    if (start == 0) {
        std::cout << "You start." << std::endl;
    } else {
        std::cout << "Opponent starts." << std::endl;
    }
    // run game
    while (true) {
        if (start == 0) {
            player->renderHitBoard();
            switch (player->runTurn()) {
                case HIT:
                    std::cout << "Hit!" << std::endl;
                    break;
                case MISS:
                    std::cout << "Miss." << std::endl;
                    break;
                case SUNK_2:
                case SUNK_3:
                case SUNK_4:
                case SUNK_5:
                    std::cout << "Sunk!" << std::endl;
                    break;
                case GAME_END:
                    std::cout << "You win!" << std::endl;
                    return;
                case ERROR:
                    std::cout << "An error has occured, try again..." << std::endl;
                    continue;
            }
            start = 1;
        } else {
            switch (opponent->runTurn()) {
                case HIT:
                    std::cout << "Hit!" << std::endl;
                    break;
                case MISS:
                    std::cout << "Miss." << std::endl;
                    break;
                case SUNK_2:
                case SUNK_3:
                case SUNK_4:
                case SUNK_5:
                    std::cout << "Sunk!" << std::endl;
                    break;
                case GAME_END:
                    std::cout << "You lose!" << std::endl;
                    return;
                case ERROR:
                    std::cout << "An error has occured, trying again..." << std::endl;
                    continue;
            }
            start = 0;
            player->render();
        }
    }
}