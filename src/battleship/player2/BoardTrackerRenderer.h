//
// Created by william on 4/3/22.
//

#ifndef BATTLESHIP_BOARDTRACKERRENDERER_H
#define BATTLESHIP_BOARDTRACKERRENDERER_H


#include "BoardTracker.h"

class BoardTrackerRenderer : public BoardTracker {
    public:
        void render(float i, float j, float ts);
        void renderHitBoard(float i, float j, float ts);
        void renderPlace(float i, float j, float ts, int row, int col, bool horizontal);

};


#endif //BATTLESHIP_BOARDTRACKERRENDERER_H
