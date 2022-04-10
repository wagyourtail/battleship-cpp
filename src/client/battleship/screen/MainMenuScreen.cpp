//
// Created by william on 4/3/22.
//

#include <string>
#include "MainMenuScreen.h"
#include "client/wagyourgui/GLFWSession.h"
#include "client/wagyourgui/elements/Button.h"
#include "client/battleship/Battleship.h"
#include "PlaceShipScreen.h"
#include "client/battleship/player/BsBotOpponent.h"
#include "MultiplayerScreen.h"

void MainMenuScreen::init(Window* window) {
    elements.push_back(
            std::make_shared<Button>(
                    width / 2.f - 400,
                    height / 2.f - 14,
                    800,
                    28,
                    parent->font,
                    "Singleplayer",
                    0,
                    0xFFa2a2a2,
                    0xFFFFFFFF,
                    0xFF000000,
                    [=](Button* btn) {
                        parent->setScreen(
                                new PlaceShipsScreen(
                                        parent,
                                        std::make_shared<GameStateMachine>(
                                                std::make_shared<BSPlayer>(),
                                                std::make_shared<BSBotOpponent>())));
                    }
            ));
    addElement(
            std::make_shared<Button>(
                    width / 2.f - 400,
                    height / 2.f + 16,
                    800,
                    28,
                    parent->font,
                    "Multiplayer",
                    0,
                    0xFFa2a2a2,
                    0xFFFFFFFF,
                    0xFF000000,
                    [=](Button* btn) {
                        parent->setScreen(new MultiplayerScreen(parent));
                    }
            ));
}

void MainMenuScreen::onRender(float mouseX, float mouseY) {
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_TEXTURE_2D);
    parent->font->drawString("Hello, World!", 0, 10);
    parent->font->drawString(std::to_string(parent->fps), 0, height - parent->font->FONT_HEIGHT);

    Battleship::atlas.bind();

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_COLOR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(100, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(100, 100);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(0.0f, 100);
    glEnd();

    Screen::onRender(mouseX, mouseY);
}