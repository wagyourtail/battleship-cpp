//
// Created by william on 3/11/22.
//

#include "BoardElement.h"
#include "src/wagyourgui/DrawableHelper.h"

using namespace DrawableHelper;

void BoardElement::onRender(float mouseX, float mouseY) {
    float ts = width / 11;
    if (renderHitBoard) {
        player->renderHitBoard(x + ts, y + ts, ts);
    } else {
        player->render(x + ts, y + ts, ts);
    }
    // render lettering
    float yCenterOffset = (ts - font->FONT_HEIGHT / 2) / 2;
    for (char i = 0; i < 10; i++) {
        drawCenteredString(font, std::string(1, ('A' + i)), x + (i + 1) * ts + ts / 2, y + yCenterOffset, 0xFFFFFFFF);
        drawCenteredString(font, std::to_string(i + 1), x + ts / 2, y + (i + 1) * ts + yCenterOffset, 0xFFFFFFFF);
    }
    if (!disabled) {
        int row = (mouseY - this->y) / ts;
        int col = (mouseX - this->x) / ts;
        if (row >= 1 && row < 11 && col >= 1 && col < 11 && !disabled) {
            // render current cell highlight
            onRenderHighlightFn(this, row - 1, col - 1);
        }
    }
}
