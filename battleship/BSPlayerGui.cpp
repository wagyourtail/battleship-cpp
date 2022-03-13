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
            builder.begin(GL_TRIANGLE_STRIP, POS_TEX)
                    .vertex(i + x * ts, j + y * ts).uv(0, 0).next()
                    .vertex(i + x * ts, j + (y + 1) * ts).uv(0, 16, 80, 64).next()
                    .vertex(i + (x + 1) * ts, j + y * ts).uv(16, 0, 80, 64).next()
                    .vertex(i + (x + 1) * ts, j + (y + 1) * ts).uv(16, 16, 80, 64)
                    .end();

            // ship
            int sid = board[x][y] >> 2;
            if (sid) {
                // horizontal or vertical
                bool horizontal = (board[x+1][y] >> 2 == sid) || (board[x-1][y] >> 2 == sid);
                // determine which section of the ship
                if (horizontal) {
                    int n = x;
                    while (board[n][y] >> 2 == sid) {
                        --n;
                    }
                    ++n;

                    //render ship section
                    int section = x - n;
                    --sid;
                    builder.begin(GL_TRIANGLE_STRIP, POS_TEX)
                            .vertex(i + x * ts, j + y * ts).uv((float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][0], (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][1], 80, 64).next()
                            .vertex(i + x * ts, j + (y + 1) * ts).uv((float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][0], (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][1] + 16, 80, 64).next()
                            .vertex(i + (x + 1) * ts, j + y * ts).uv((float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][0] + 16, (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][1], 80, 64).next()
                            .vertex(i + (x + 1) * ts, j + (y + 1) * ts).uv((float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][0] + 16, (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][1] + 16, 80, 64)
                            .end();
                } else {
                    int n = y;
                    while (board[x][n] >> 2 == sid) {
                        --n;
                    }
                    ++n;

                    // render ship section rotated 90 degrees counter clockwise
                    int section = Battleship::SHIP_LENGTHS[--sid] - (y - n) - 1;
                    builder.begin(GL_TRIANGLE_STRIP, POS_TEX)
                            .vertex(i + x * ts, j + y * ts).uv((float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][0] + 16, (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][1], 80, 64).next()
                            .vertex(i + x * ts, j + (y + 1) * ts).uv((float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][0], (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][1], 80, 64).next()
                            .vertex(i + (x + 1) * ts, j + y * ts).uv((float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][0] + 16, (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][1] + 16, 80, 64).next()
                            .vertex(i + (x + 1) * ts, j + (y + 1) * ts).uv((float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][0], (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][1] + 16, 80, 64)
                            .end();
                }
            }

            // hit/miss
            if (board[x][y] & 1) {
                builder.begin(GL_TRIANGLE_STRIP, POS_TEX)
                        .color(board[x][y] & 2 ? 0xFFFF0000 : 0xFFFFFFFF)
                        .vertex(i + x * ts, j + y * ts).uv(48, 16, 80, 64).next()
                        .vertex(i + x * ts, j + (y + 1) * ts).uv(48, 32, 80, 64).next()
                        .vertex(i + (x + 1) * ts, j + y * ts).uv(64, 16, 80, 64).next()
                        .vertex(i + (x + 1) * ts, j + (y + 1) * ts).uv(64, 32, 80, 64)
                        .end();
            }


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

            // hit/miss
            if (hitBoard[x][y] & 1) {
                builder.begin(GL_TRIANGLE_STRIP, POS_COL_TEX)
                    .color(hitBoard[x][y] & 2 ? 0xFFFF0000 : 0xFFFFFFFF)
                    .vertex(i + x * ts, j + y * ts).uv(48, 16, 80, 64).next()
                    .vertex(i + x * ts, j + (y + 1) * ts).uv(48, 32, 80, 64).next()
                    .vertex(i + (x + 1) * ts, j + y * ts).uv(64, 16, 80, 64).next()
                    .vertex(i + (x + 1) * ts, j + (y + 1) * ts).uv(64, 32, 80, 64)
                    .end();
            }
        }
    }
}