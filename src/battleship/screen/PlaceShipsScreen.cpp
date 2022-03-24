//
// Created by william on 3/10/22.
//

#include "PlaceShipsScreen.h"

#include <memory>
#include "src/battleship/screen/elements/BoardElement.h"
#include "src/wagyourgui/GLFWSession.h"
#include "src/wagyourgui/DrawableHelper.h"
#include "PlayScreen.h"
#include "src/wagyourgui/elements/Button.h"


void PlaceShipsScreen::init(Window* window) {
    float ts;
    ts = height / 11;
    elements.push_back(
            board = std::make_shared<BoardElement>(
                    0,
                    0,
                    ts * 11,
                    parent->font,
                    gameSession->player,
                    [=](BoardElement* element, int row, int col, int button) {
                        if (button == GLFW_MOUSE_BUTTON_LEFT) {
                            this->placeShip(element, row, col);
                        } else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
                            this->horizontal = !this->horizontal;
                        }
                    },
                    [=](BoardElement* element, int row, int col) {
                        gameSession->player->renderPlace(0, 0, ts, row, col, this->horizontal);
                    }
            ));


    // calc room for controls on right
    float controlRoom = width - height;

    elements.push_back(
            std::make_shared<Button>(
                    height,
                    height - 30,
                    controlRoom,
                    20,
                    parent->font,
                    "Undo",
                    0,
                    0xFF7F7F7F,
                    0xFFFFFFFF,
                    0xFF000000,
                    [=](Button* button) {
                        shipsPlaced = gameSession->player->undoPlace();
                    }
            ));
}

void PlaceShipsScreen::onRender(float mouseX, float mouseY) {
    Screen::onRender(mouseX, mouseY);

    if (shipsPlaced == 5) {
        board->setDisabled(true);
        if (gameSession->pollSetup()) {
            gameSession->finishPlace();
            parent->setScreen(new PlayScreen(parent, gameSession));
            return;
        }
    }

    // calc room for controls on right
    float controlRoom = width - height;

    float ts = height / 5.5;

    glPushMatrix();
    glTranslatef(height, 0, 0);
    glScalef(.5, .5, 1);
    DrawableHelper::drawCenteredString(parent->font, "Place your ships", controlRoom, 20, 0xFFFFFFFF);
    DrawableHelper::drawString(parent->font, "Current Ship: ", 0, ts, 0xFFFFFFFF);
    DrawableHelper::drawCenteredString(
            parent->font,
            Battleship::SHIP_NAMES[shipsPlaced],
            controlRoom,
            ts + 30,
            0xFFFFFFFF
    );
    glPopMatrix();
}

void PlaceShipsScreen::placeShip(BoardElement* element, int row, int col) {
    bool success = gameSession->player->placeShip({col, row, Battleship::SHIP_LENGTHS[shipsPlaced], horizontal});
    if (success) {
        ++shipsPlaced;
    }
}