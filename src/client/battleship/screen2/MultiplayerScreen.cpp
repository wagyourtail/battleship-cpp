//
// Created by william on 4/6/22.
//

#include "MultiplayerScreen.h"
#include "client/wagyourgui/GLFWSession.h"
#include "client/wagyourgui/elements/TextInput.h"
#include "client/wagyourgui/DrawableHelper.h"
#include "ConnectingScreen.h"
#include "MainMenuScreen2.h"
#include <algorithm>
#include <string>

using namespace DrawableHelper;

void MultiplayerScreen::init(Window* window) {

    addElement(std::make_shared<Button>(
            5, height / 2 + 10, width / 2 - 10, 20,
            parent->font, "Host", 0, 0xFF4f4f4f, 0xFFFFFFFF, 0xFF000000,
            [=](Button* b) {
                parent->setScreen(new ConnectingScreen(parent));
            }
    ));
    std::shared_ptr<TextInput> joinCode;
    joinCode = addElement(std::make_shared<TextInput>(
            width / 2 + 5, height / 2 - 15, width / 2 - 10, 20, parent->font, 0xFF101010, 0xFF000000, 0xFF4040FF, 0xFFFFFFFF, "",
            [](Button* btn) {}, [=](std::string& str) {
                https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
                std::transform(str.begin(), str.end(),str.begin(), ::toupper);
            }
    ));

    joinCode->regex = std::regex("[a-zA-Z0-9]{0,5}");

    addElement(std::make_shared<Button>(
            width / 2 + 5, height / 2 + 10, width / 2 - 10, 20,
            parent->font, "Join", 0, 0xFF4f4f4f, 0xFFFFFFFF, 0xFF000000,
            [=](Button* b) {
                if (joinCode->content.length() == 5)
                    parent->setScreen(new ConnectingScreen(parent, joinCode->content));
            }
    ));

    addElement(std::make_shared<Button>(
            5, height - 35, width / 2 - 10, 20,
            parent->font, "Back", 0, 0xFF4f4f4f, 0xFFFFFFFF, 0xFF000000,
            [=](Button* b) {
                parent->setScreen(new MainMenuScreen2(parent));
            }
    ));
}

void MultiplayerScreen::onRender(float mouseX, float mouseY) {
    drawCenteredString(parent->font, "Multiplayer", width / 2, 15, 0xFFFFFFFF);
    Screen::onRender(mouseX, mouseY);
}
