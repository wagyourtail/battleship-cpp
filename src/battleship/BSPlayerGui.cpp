//
// Created by william on 3/10/22.
//

#include "wagyourgui/GLBuilder.h"
#include "BSPlayerGui.h"

void BSPlayerGui::render(float i, float j, float ts) {
    Battleship::atlas.bind();
    GLBuilder& builder = GLBuilder::getImmediate();
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            //background
            builder.begin(GL_TRIANGLE_STRIP, GLBuilder::POS_TEX)
                   .vertex(i + x * ts, j + y * ts).uv(0, 0).next()
                   .vertex(i + x * ts, j + (y + 1) * ts).uv(0, 16, 80, 64).next()
                   .vertex(i + (x + 1) * ts, j + y * ts).uv(16, 0, 80, 64).next()
                   .vertex(i + (x + 1) * ts, j + (y + 1) * ts).uv(16, 16, 80, 64)
                   .end();

            // ship
            int sid = board[x][y] >> 2;
            if (sid) {
                // horizontal or vertical
                bool horizontal = (board[x + 1][y] >> 2 == sid) || (board[x - 1][y] >> 2 == sid);
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
                    builder.begin(GL_TRIANGLE_STRIP, GLBuilder::POS_TEX)
                           .vertex(i + x * ts, j + y * ts)
                           .uv((float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][0],
                                   (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][1],
                                   80,
                                   64
                           )
                           .next()

                           .vertex(i + x * ts, j + (y + 1) * ts)
                           .uv((float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][0],
                                   (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][1] + 16,
                                   80,
                                   64
                           )
                           .next()
                           .vertex(i + (x + 1) * ts, j + y * ts)
                           .uv(
                                   (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][0] + 16,
                                   (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][1],
                                   80,
                                   64
                           )
                           .next()

                           .vertex(i + (x + 1) * ts, j + (y + 1) * ts)
                           .uv(
                                   (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][0] + 16,
                                   (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][1] + 16,
                                   80,
                                   64
                           )
                           .end();
                } else {
                    int n = y;
                    while (board[x][n] >> 2 == sid) {
                        --n;
                    }
                    ++n;

                    // render ship section rotated 90 degrees counter clockwise
                    int section = Battleship::SHIP_LENGTHS[--sid] - (y - n) - 1;
                    builder.begin(GL_TRIANGLE_STRIP, GLBuilder::POS_TEX)
                           .vertex(i + x * ts, j + y * ts)
                           .uv(
                                   (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][0] + 16,
                                   (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][1],
                                   80,
                                   64
                           )
                           .next()

                           .vertex(i + x * ts, j + (y + 1) * ts)
                           .uv(
                                   (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][0],
                                   (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][1],
                                   80,
                                   64
                           )
                           .next()

                           .vertex(i + (x + 1) * ts, j + y * ts)
                           .uv(
                                   (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][0] + 16,
                                   (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][1] + 16,
                                   80,
                                   64
                           )
                           .next()

                           .vertex(i + (x + 1) * ts, j + (y + 1) * ts)
                           .uv(
                                   (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][0],
                                   (float) Battleship::SHIP_RENDER_LOCATIONS[sid][section][1] + 16,
                                   80,
                                   64
                           )
                           .end();
                }
            }

            // hit/miss
            if (board[x][y] & 1) {
                builder.begin(GL_TRIANGLE_STRIP, GLBuilder::POS_COL_TEX)
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
    GLBuilder& builder = GLBuilder::GLBuilder::getImmediate();
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            //background
            builder.begin(GL_TRIANGLE_STRIP, GLBuilder::POS_TEX)
                   .vertex(i + x * ts, j + y * ts).uv(0, 0).next()
                   .vertex(i + x * ts, j + (y + 1) * ts).uv(0, 16, 80, 64).next()
                   .vertex(i + (x + 1) * ts, j + y * ts).uv(16, 0, 80, 64).next()
                   .vertex(i + (x + 1) * ts, j + (y + 1) * ts).uv(16, 16, 80, 64)
                   .end();

            // hit/miss
            if (hitBoard[x][y] & 1) {
                builder.begin(GL_TRIANGLE_STRIP, GLBuilder::POS_COL_TEX)
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

void BSPlayerGui::renderPlace(float i, float j, float ts, int row, int col, bool horizontal) {
    // get current ship length and id
    int len = Battleship::SHIP_LENGTHS[numShips];
    GLBuilder& builder = GLBuilder::getImmediate();
    Battleship::atlas.bind();
    if (horizontal) {
        // initialize with collides with edge
        bool collides = col + len > 10;
        if (!collides) {
            // check collides with ship
            for (int i = 0; i < len; ++i) {
                if (board[col + i][row] & 2) {
                    collides = true;
                    break;
                }
            }
        }
        int y = row + 1;
        for (int n = 0, x = col + 1; x < 11 && n < len; ++n, ++x) {
            builder.begin(GL_TRIANGLE_STRIP, GLBuilder::POS_COL_TEX)
                   .color(collides ? 0xFFFF6666 : 0xFFFFFFFF)
                   .vertex(i + x * ts, j + y * ts)
                   .uv(
                           (float) Battleship::SHIP_RENDER_LOCATIONS[numShips][n][0],
                           (float) Battleship::SHIP_RENDER_LOCATIONS[numShips][n][1],
                           80,
                           64
                   )
                   .next()

                   .vertex(i + x * ts, j + (y + 1) * ts)
                   .uv(
                           (float) Battleship::SHIP_RENDER_LOCATIONS[numShips][n][0],
                           (float) Battleship::SHIP_RENDER_LOCATIONS[numShips][n][1] + 16,
                           80,
                           64
                   )
                   .next()

                   .vertex(i + (x + 1) * ts, j + y * ts)
                   .uv(
                           (float) Battleship::SHIP_RENDER_LOCATIONS[numShips][n][0] + 16,
                           (float) Battleship::SHIP_RENDER_LOCATIONS[numShips][n][1],
                           80,
                           64
                   )
                   .next()

                   .vertex(i + (x + 1) * ts, j + (y + 1) * ts)
                   .uv(
                           (float) Battleship::SHIP_RENDER_LOCATIONS[numShips][n][0] + 16,
                           (float) Battleship::SHIP_RENDER_LOCATIONS[numShips][n][1] + 16,
                           80,
                           64
                   )
                   .end();
        }
    } else {
        // initialize with collides with edge
        bool collides = row + len > 10;
        if (!collides) {
            // check collides with ship
            for (int i = 0; i + row < 10 && i < len; ++i) {
                if (board[col][row + i] & 2) {
                    collides = true;
                    break;
                }
            }
        }

        int x = col + 1;
        for (int n = len - 1, y = row + 1; y < 11 && n >= 0; --n, ++y) {
            builder.begin(GL_TRIANGLE_STRIP, GLBuilder::POS_COL_TEX)
                   .color(collides ? 0xFFFF6666 : 0xFFFFFFFF)
                   .vertex(i + x * ts, j + y * ts)
                   .uv(
                           (float) Battleship::SHIP_RENDER_LOCATIONS[numShips][n][0] + 16,
                           (float) Battleship::SHIP_RENDER_LOCATIONS[numShips][n][1],
                           80,
                           64
                   )
                   .next()

                   .vertex(i + x * ts, j + (y + 1) * ts)
                   .uv(
                           (float) Battleship::SHIP_RENDER_LOCATIONS[numShips][n][0],
                           (float) Battleship::SHIP_RENDER_LOCATIONS[numShips][n][1],
                           80,
                           64
                   )
                   .next()

                   .vertex(i + (x + 1) * ts, j + y * ts)
                   .uv(
                           (float) Battleship::SHIP_RENDER_LOCATIONS[numShips][n][0] + 16,
                           (float) Battleship::SHIP_RENDER_LOCATIONS[numShips][n][1] + 16,
                           80,
                           64
                   )
                   .next()

                   .vertex(i + (x + 1) * ts, j + (y + 1) * ts)
                   .uv(
                           (float) Battleship::SHIP_RENDER_LOCATIONS[numShips][n][0],
                           (float) Battleship::SHIP_RENDER_LOCATIONS[numShips][n][1] + 16,
                           80,
                           64
                   )
                   .end();
        }
    }
}

int BSPlayerGui::undoPlace() {
    --numShips;
    Battleship::Ship ship = ships[numShips];
    if (ship.horizontal) {
        for (int i = ship.x; i < ship.x + ship.length; ++i) {
            board[i][ship.y] = 0;
        }
    } else {
        for (int i = ship.y; i < ship.y + ship.length; ++i) {
            board[ship.x][i] = 0;
        }
    }
    return numShips;
}
