//
// Created by william on 4/6/22.
//

#include "MultiplayerScreen.h"
#include "client/wagyourgui/GLFWSession.h"
#include "client/wagyourgui/elements/TextInput.h"
#include "client/wagyourgui/DrawableHelper.h"
#include "ConnectingScreen.h"
#include "MainMenuScreen.h"
#include <algorithm>
#include <string>

using namespace DrawableHelper;

void MultiplayerScreen::init(Window* window) {

    std::shared_ptr<TextInput> serverIP;
    serverIP = addElement(
            std::make_shared<TextInput>(
                    5,
                    height / 2 - 55,
                    width - 10,
                    20,
                    parent->font,
                    0xFF101010,
                    0xFF000000,
                    0xFF4040FF,
                    0xFFFFFFFF,
                    "127.0.0.1",
                    [](Button* btn) {},
                    [](std::string& str) {}
            ));
    serverIP->regex = "\\d*\\.?\\d*\\.?\\d*\\.?\\d*";

    addElement(
            std::make_shared<Button>(
                    5, height / 2 + 10, width / 2 - 10, 20,
                    parent->font, "Host", 0, 0xFF4f4f4f, 0xFFFFFFFF, 0xFF000000,
                    [=](Button* b) {
                        if (regex_match(serverIP->content, std::regex("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?(\\.|$)){4}"))) {
                            parent->setScreen(new ConnectingScreen(parent, serverIP->content));
                        }
                    }
            ));
    std::shared_ptr<TextInput> joinCode;

    joinCode = addElement(
            std::make_shared<TextInput>(
                    width / 2 + 5,
                    height / 2 - 15,
                    width / 2 - 10,
                    20,
                    parent->font,
                    0xFF101010,
                    0xFF000000,
                    0xFF4040FF,
                    0xFFFFFFFF,
                    "",
                    [](Button* btn) {},
                    [=](std::string& str) {
                        https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
                        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
                    }
            ));

    joinCode->regex = std::regex("[a-zA-Z0-9]{0,5}");

    addElement(
            std::make_shared<Button>(
                    width / 2 + 5, height / 2 + 10, width / 2 - 10, 20,
                    parent->font, "Join", 0, 0xFF4f4f4f, 0xFFFFFFFF, 0xFF000000,
                    [=](Button* b) {
                        if (joinCode->content.length() == 5) {
                            if (regex_match(serverIP->content, std::regex("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){4}$"))) {
                                parent->setScreen(new ConnectingScreen(parent, serverIP->content, joinCode->content));
                            }
                        }
                    }
            ));

    addElement(
            std::make_shared<Button>(
                    5, height - 35, width / 2 - 10, 20,
                    parent->font, "Back", 0, 0xFF4f4f4f, 0xFFFFFFFF, 0xFF000000,
                    [=](Button* b) {
                        parent->setScreen(new MainMenuScreen(parent));
                    }
            ));
}

void MultiplayerScreen::onRender(float mouseX, float mouseY) {
    drawCenteredString(parent->font, "Multiplayer", width / 2, 15, 0xFFFFFFFF);
    glPushMatrix();
    glTranslatef(width / 2, height / 2 - 70, 0);
    glScalef(0.5, 0.5, 1);
    drawCenteredString(parent->font, "Server IP", 0, 0, 0xFFFFFFFF);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3 * width / 4, height / 2 - 30, 0);
    glScalef(0.5, 0.5, 1);
    drawCenteredString(parent->font, "Join Code", 0, 0, 0xFFFFFFFF);
    glPopMatrix();

    Screen::onRender(mouseX, mouseY);
}
