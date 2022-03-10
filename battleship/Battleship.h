//
// Created by william on 3/10/22.
//

#ifndef BATTLESHIP_BATTLESHIP_H
#define BATTLESHIP_BATTLESHIP_H

namespace Battleship {
    constexpr int SHIP_LENGTHS[5] = {5, 4, 3, 3, 2};
}

struct Ship {
    int x;
    int y;
    int length;
    bool horizontal;
};

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

#endif //BATTLESHIP_BATTLESHIP_H
