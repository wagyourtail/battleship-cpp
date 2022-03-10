//
// Created by william on 3/10/22.
//

#ifndef BATTLESHIP_BSPLAYERGUI_H
#define BATTLESHIP_BSPLAYERGUI_H

#include "BSPlayer.h"

class BSPlayerGui : public BSPlayer {
    public:
        int ts{}, i{}, j{};
    public:
        void render() override;
        void renderHitBoard() override;

};

#endif //BATTLESHIP_BSPLAYERGUI_H
