//
// Created by william on 3/10/22.
//

#include "PlaceShipsScreen.h"
#include "../wagyourgui/GLBuilder.h"
#include "../wagyourgui/elements/Button.h"
#include "BSBot.h"
#include "MainMenuScreen.h"

void MainMenuScreen::init(Window *window) {
    elements.push_back(new Button(width / 2.f - 400, height / 2.f - 14, 800, 28, session->font, "Start Game", 0, 0xFFa2a2a2, 0xFFFFFFFF, 0xFF000000, [=] (Button *btn) {
        auto *gamerunner = new GameSession(new BSPlayerGui(), new BSBot());
        session->setScreen(new PlaceShipsScreen(session, gamerunner));
    }));
}

void MainMenuScreen::onRender(float mouseX, float mouseY) {
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_TEXTURE_2D);
    session->font->drawString("Hello, World!", 0, 10);
    session->font->drawString(std::to_string(session->fps), 0, height - session->font->FONT_HEIGHT);

    test.bind();

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_COLOR);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(100, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(100, 100);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 100);
    glEnd();

    Screen::onRender(mouseX, mouseY);
}