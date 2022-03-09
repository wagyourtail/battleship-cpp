//
// Created by william on 3/1/22.
//

#ifndef CS225_PROJECT_BATTLESHIP_H
#define CS225_PROJECT_BATTLESHIP_H

#include <iostream>
#include <random>

enum Status {
    HIT,
    MISS,
    SUNK_2,
    SUNK_3,
    SUNK_4,
    SUNK_5,
    GAME_END,
    ERROR
};

class BSOpponent {
    protected:
        BSOpponent* opponent;
    public:
        void setOpponent(BSOpponent* opp) {
            opponent = opp;
        };
        virtual Status attackedAt(int x, int y) = 0;
        virtual Status attack(int x, int y) = 0;
        virtual Status runTurn() = 0;
        virtual void setup() = 0;
};

struct Ship {
    int x;
    int y;
    int length;
    bool horizontal;
};

// board bits
// 1 = hit
// 2 = ship
// 3-end = ship_id

class BSLocal : public BSOpponent {
    protected:
        int board[10][10]{};
        int hitBoard[10][10]{};
        int numShips{};
        int numSpacesAlive{};

    protected:
        Status attackedAt(int x, int y) override;
        Status attack(int x, int y) override;
        virtual bool placeShip(Ship ship);
    private:
        int sunkCheck(int x, int y);
    protected:
        void placeRandomShip(int length);
};

namespace Battleship {
    int SHIP_LENGTHS[] = {2, 3, 3, 4, 5};
}

class BSPlayer : public BSLocal {
    public:
        void setup() override {
            for (auto & ship : Battleship::SHIP_LENGTHS) {
                render();
                promptShipPlacement(ship);
            }
        }
        Status attackedAt(int x, int y) override {
            char xchar = x + 'a';
            std::cout << "opponent attacked at " << xchar << y + 1 << "!" << std::endl;
            return BSLocal::attackedAt(x, y);
        };
        void render();
        void renderHitBoard();
        void promptShipPlacement(int length);
        Status runTurn() override;
};

class BSBot : public BSLocal {
    public:
        void setup() override {
            for (auto & i : Battleship::SHIP_LENGTHS) {
                placeRandomShip(i);
            }
        }
        Status runTurn() override;
};

class GameRunner {
    private:
        BSPlayer* player;
        BSOpponent* opponent;
    public:
        GameRunner(BSPlayer* player, BSOpponent* opponent) : player(player), opponent(opponent) {
            player->setOpponent(opponent);
            opponent->setOpponent(player);
        }
        virtual void runGame();
};

#endif //CS225_PROJECT_BATTLESHIP_H
