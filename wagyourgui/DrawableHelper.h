//
// Created by william on 3/9/22.
//

#ifndef BATTLESHIP_DRAWABLEHELPER_H
#define BATTLESHIP_DRAWABLEHELPER_H

#include "GLBuilder.h"
#include "Font.h"

namespace DrawableHelper {
    void rect(float x1, float y1, float x2, float y2, uint32_t argb);
    void drawCenteredString(Font* font, const std::string& text, float x, float y, uint32_t argb);
    void drawString(Font* font, const std::string& text, float x, float y, uint32_t argb);
    void drawTrimmedString(Font* font, const std::string& text, float x, float y, float width, uint32_t argb);
};



#endif //BATTLESHIP_DRAWABLEHELPER_H
