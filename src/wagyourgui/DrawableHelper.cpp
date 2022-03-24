//
// Created by william on 3/9/22.
//

#include "DrawableHelper.h"
#include "GLBuilder.h"

namespace DrawableHelper {
    GLBuilder& builder = GLBuilder::getImmediate();
}

void DrawableHelper::rect(float x1, float y1, float x2, float y2, uint32_t argb) {
    if (x1 > x2) {
        float temp = x1;
        x1 = x2;
        x2 = temp;
    }

    if (y1 > y2) {
        float temp = y1;
        y1 = y2;
        y2 = temp;
    }

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_COLOR);

    builder.begin(GL_TRIANGLE_STRIP)
           .color(argb)
           .vertex(x1, y1).next()
           .vertex(x2, y1).next()
           .vertex(x1, y2).next()
           .vertex(x2, y2)
           .end();
}

void DrawableHelper::drawCenteredString(Font* font, const std::string& text, float x, float y, uint32_t argb) {
    builder.color(argb);
    float width = font->getWidth(text);
    glEnable(GL_TEXTURE_2D);
    font->drawString(text, x - width / 2, y);
}

void DrawableHelper::drawString(Font* font, const std::string& text, float x, float y, uint32_t argb) {
    builder.color(argb);
    glEnable(GL_TEXTURE_2D);
    font->drawString(text, x, y);
}

void
DrawableHelper::drawTrimmedString(Font* font, const std::string& text, float x, float y, float width, uint32_t argb) {
    builder.color(argb);
    glEnable(GL_TEXTURE_2D);
    font->drawTrimmedString(text, x, y, width);
}