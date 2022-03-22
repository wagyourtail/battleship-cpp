//
// Created by william on 3/9/22.
//

#include "Button.h"
#include "src/wagyourgui/DrawableHelper.h"

using namespace DrawableHelper;

void Button::onRender(float mouseX, float mouseY) {
    bool hover = mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;

    // Draw background
    rect(x, y, x + width, y + height, hover ? hoverColor : color);

    // Draw border
    rect(x, y, x + 1, y + height, borderColor);
    rect(x + width - 1, y, x + width, y + height, borderColor);
    rect(x + 1, y, x + width - 1, y + 1, borderColor);
    rect(x + 1, y + height - 1, x + width - 1, y + height, borderColor);

    // Draw text
    float w = font->getWidth(text);
    if (w < width - 4) {
        drawCenteredString(font, text, x + width / 2, y + height / 2 - font->FONT_HEIGHT / 2, hover ? hoverTextColor : textColor);
    } else {
        drawTrimmedString(font, text, x + 2, y + height / 2 - font->FONT_HEIGHT / 2, width - 4, hover ? hoverTextColor : textColor);
    }
}