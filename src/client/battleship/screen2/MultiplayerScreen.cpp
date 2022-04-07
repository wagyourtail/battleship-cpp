//
// Created by william on 4/6/22.
//

#include "MultiplayerScreen.h"
#include "client/wagyourgui/GLFWSession.h"
#include "client/wagyourgui/elements/TextInput.h"
#include "client/wagyourgui/DrawableHelper.h"
#include <iostream>

using namespace DrawableHelper;

void MultiplayerScreen::init(Window* window) {
    addElement(std::make_shared<TextInput>(
            0, 25, 200, 25, parent->font, 0xFF101010, 0xFF000000, 0xFF4040FF, 0xFFFFFFFF, "",
            [](Button* btn) {}, [](const std::string& str) {
                std::cout << str << std::endl;
            }
    ));
}

void MultiplayerScreen::onRender(float mouseX, float mouseY) {
    drawString(parent->font, "Multiplayer", 0, 0, 0xFFFFFFFF);
    Screen::onRender(mouseX, mouseY);
}
