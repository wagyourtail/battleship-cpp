//
// Created by william on 3/10/22.
//

#include "BSPlayer.h"
#include "battleship/Battleship.h"
#include <iostream>
#include <random>
#include <string>

void BSPlayer::render() {
    std::string hit = "\033[31m⬛\033[0m";
    std::string miss = "\033[30;1m⬛\033[0m";
    std::string none = "\033[37m⬜\033[0m";

    std::string ansi_background_reset = "\033[0m";
    std::string ansi_background_gray = "\033[100m";

    std::cout << "hit: " << hit << ", miss: " << miss << ", none: " << none << std::endl;
    std::cout << std::endl;
    std::cout << "   ａ ｂ ｃ ｄ ｅ ｆ ｇ ｈ ｉ ｊ" << std::endl;
    for (int y = 0; y < 10; ++y) {
        std::cout << y + 1 << " ";
        if (y != 9) {
            std::cout << " ";
        }
        for (int x = 0; x < 10; ++x) {
            if (board[x][y] & 1) {
                if (board[x][y] & 2) {
                    std::cout << ansi_background_gray << hit << ansi_background_reset;
                } else {
                    std::cout << miss;
                }
            } else {
                if (board[x][y] & 2) {
                    std::cout << ansi_background_gray << none << ansi_background_reset;
                } else {
                    std::cout << none;
                }
            }
            if (x < 9) {
                if (board[x + 1][y] >> 2 == board[x][y] >> 2 && board[x + 1][y] >> 2 != 0) {
                    std::cout << ansi_background_gray << " " << ansi_background_reset;
                } else {
                    std::cout << " ";
                }
            }
        }
        std::cout << std::endl;
        if (y < 9) {
            std::cout << "   ";
            for (auto& x: board) {
                if (x[y + 1] >> 2 == x[y] >> 2 && x[y + 1] >> 2 != 0) {
                    std::cout << ansi_background_gray << "　" << ansi_background_reset << " ";
                } else {
                    std::cout << "　 ";
                }
            }
            std::cout << std::endl;
        }
    }
}

void BSPlayer::renderHitBoard() {
    std::string hit = "\033[31m⬛\033[0m";
    std::string miss = "\033[30;1m⬛\033[0m";
    std::string none = "\033[37m⬜\033[0m";

    std::cout << "hit: " << hit << ", miss: " << miss << ", none: " << none << std::endl;
    std::cout << std::endl;
    std::cout << "    ａ ｂ ｃ ｄ ｅ ｆ ｇ ｈ ｉ ｊ" << std::endl;
    for (int y = 0; y < 10; ++y) {
        std::cout << y + 1 << "  ";
        if (y != 9) {
            std::cout << " ";
        }
        for (int x = 0; x < 10; ++x) {
            if (hitBoard[x][y] & 1) {
                if (hitBoard[x][y] & 2) {
                    std::cout << hit;
                } else {
                    std::cout << miss;
                }
            } else {
                std::cout << none;
            }
            if (x < 9) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
        if (y < 9) {
            std::cout << "   ";
            for (auto& x: hitBoard) {
                std::cout << "　 ";
            }
            std::cout << std::endl;
        }
    }
}

void BSPlayer::promptShipPlacement(int length) {
    bool placed = false;
    do {
        std::cout << "Your board:" << std::endl;
        render();
        std::cout << "Place your " << length << " unit ship." << std::endl;
        std::cout << "Enter the coordinates of the top/left of the ship. or 'r' for random" << std::endl;
        std::cout << "Example: a1" << std::endl;
        std::string input;
        std::cin >> input;
        if (input.length() != 2 && input.substr(1) != "10") {
            if (input == "r") {
                placeRandomShip(length);
                placed = true;
            } else {
                std::cout << "Invalid input" << std::endl;
            }
            continue;
        }
        int x = input[0] - 'a';
        if (input[1] < '0' || input[1] > '9') {
            std::cout << "Invalid input" << std::endl;
            continue;
        }
        int y = std::stoi(input.substr(1)) - 1;
        if (x < 0 || x > 9 || y < 0 || y > 9) {
            std::cout << "Invalid input." << std::endl;
            continue;
        }
        std::cout << "Enter the direction of the ship. (h for horizontal, v for vertical)" << std::endl;
        char dir;
        std::cin >> dir;
        if (dir != 'h' && dir != 'v') {
            std::cout << "Invalid input." << std::endl;
            continue;
        }
        placed = placeShip({x, y, length, dir == 'h'});
        if (!placed) {
            std::cout << "Invalid placement. either out of board or overlapping" << std::endl;
        }
    } while (!placed);
}

Battleship::Status BSPlayer::runTurn() {
    std::cout << "Your turn." << std::endl;
    while (true) {
        std::cout << "Enter the coordinates of the shot. or 'r' for random" << std::endl;
        std::cout << "Example: a1" << std::endl;
        std::string input;
        std::cin >> input;
        if (input == "r") {
            std::random_device rd;
            std::uniform_int_distribution<int> dist(0, 9);
            int x, y;
            do {
                x = dist(rd);
                y = dist(rd);
            } while (hitBoard[x][y] & 1);
            return attack(x, y);
        }
        if (input.length() != 2 && input.substr(1) != "10") {
            std::cout << "Invalid input" << std::endl;
            continue;
        }
        int x = input[0] - 'a';
        if (input[1] < '0' || input[1] > '9') {
            std::cout << "Invalid input" << std::endl;
            continue;
        }
        int y = std::stoi(input.substr(1)) - 1;
        if (x < 0 || x > 9 || y < 0 || y > 9) {
            std::cout << "Invalid input." << std::endl;
            continue;
        }
        return attack(x, y);
    }
}