//
// Created by william on 3/10/22.
//

#include "../wagyourgui/GLBuilder.h"
#include "BSPlayerGui.h"

void BSPlayerGui::render() {

//        if (width < height) {
//            ts = width / 12;
//            i = ts;
//            j = (height - width) / 2;
//        } else {
//            i = (width - height) / 2;
//            ts = height / 12;
//            j = ts;
//        }
//      }

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

void BSPlayerGui::renderHitBoard() {
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