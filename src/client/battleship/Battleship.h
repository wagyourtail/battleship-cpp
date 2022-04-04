//
// Created by william on 3/10/22.
//

#ifndef BATTLESHIP_BATTLESHIP_H
#define BATTLESHIP_BATTLESHIP_H

#include "client/wagyourgui/Texture.h"

namespace Battleship {
    constexpr int SHIP_LENGTHS[5] = {5, 4, 3, 3, 2};

    /* @formatter:off */
    // clion formatter putting a 2nd space after first ,
    constexpr int SHIP_RENDER_LOCATIONS[5][5][2] = {
            {
                    {0, 48}, {16, 48}, {32, 48}, {48, 48}, {64, 48}
            },
            {
                    {0, 32}, {16, 32}, {32, 32}, {48, 32}
            },
            {
                    {64, 0}, {64, 16}, {64, 32}
            },
            {
                    {0, 16}, {16, 16}, {32, 16}
            },
            {
                    {32, 0}, {48, 0}
            }
    };
    /* @formatter:on */

    constexpr char* SHIP_NAMES[5] = {
            (char*) "Aircraft Carrier",
            (char*) "Battleship",
            (char*) "Submarine",
            (char*) "Destroyer",
            (char*) "Patrol Boat"
    };

    extern Texture atlas;

    struct Ship {
        int x;
        int y;
        int length;
        bool horizontal;
    };

    enum Status {
        WAITING,
        HIT,
        MISS,
        SUNK_2,
        SUNK_3,
        SUNK_4,
        SUNK_5,
        GAME_END,
        ERROR
    };
}

#endif //BATTLESHIP_BATTLESHIP_H
