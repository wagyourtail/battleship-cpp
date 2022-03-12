//
// Created by william on 3/10/22.
//

#include "wagyourgui/GLBuilder.h"
#include "BSPlayerGui.h"

void BSPlayerGui::render(float i, float j, float ts) {
    Battleship::atlas.bind();
    GLBuilder builder = GLBuilder::getBuilder();
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            //background
            builder.begin(GL_TRIANGLE_STRIP, POS_COL_TEX).color(0xFFFFFFFF)
                    .vertex(i + x * ts, j + y * ts).uv(0, 0).next()
                    .vertex(i + x * ts, j + (y + 1) * ts).uv(0, 16, 80, 64).next()
                    .vertex(i + (x + 1) * ts, j + y * ts).uv(16, 0, 80, 64).next()
                    .vertex(i + (x + 1) * ts, j + (y + 1) * ts).uv(16, 16, 80, 64)
                    .end();


        }
    }
}

void BSPlayerGui::renderHitBoard(float i, float j, float ts) {
    Battleship::atlas.bind();
    GLBuilder builder = GLBuilder::getBuilder();
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            //background
            builder.begin(GL_TRIANGLE_STRIP, POS_TEX)
                    .vertex(i + x * ts, j + y * ts).uv(0, 0)
                    .vertex(i + x * ts, j + (y + 1) * ts).uv(0, 1, 80, 64)
                    .vertex(i + (x + 1) * ts, j + y * ts).uv(1, 0, 80, 64)
                    .vertex(i + (x + 1) * ts, j + (y + 1) * ts).uv(1, 1, 80, 64)
                    .end();


        }
    }
}