//
// Created by william on 3/31/22.
//

#ifndef BATTLESHIP_BSPLAYER2_H
#define BATTLESHIP_BSPLAYER2_H

#include <memory>
#include "battleship/Battleship.h"

class BSPlayer2 {
    public:
        void hitboard(const std::shared_ptr<Battleship::Status>& status, int x, int y);
        Battleship::Status attacked(int x, int y);
};


#endif //BATTLESHIP_BSPLAYER2_H
