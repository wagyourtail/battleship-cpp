//
// Created by william on 4/3/22.
//

#include "client/wagyourgui/GLFWSession.h"
#include "PlaceShipScreen2.h"
#include "client/wagyourgui/elements/Button.h"
#include "client/wagyourgui/DrawableHelper.h"
#include "SyncOpponentScreen.h"
#include "MainMenuScreen2.h"

void PlaceShipsScreen2::init(Window* window) {
    float ts;
    ts = height / 11;
    elements.push_back(
            board = std::make_shared<BoardElement2>(
                    0,
                    0,
                    ts * 11,
                    parent->font,
                    gameSession->getPlayer(),
                    [=](BoardElement2* element, int row, int col, int button) {
                        if (button == GLFW_MOUSE_BUTTON_LEFT) {
                            this->placeShip(element, row, col);
                        } else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
                            this->horizontal = !this->horizontal;
                        }
                    },
                    [=](BoardElement2* element, int row, int col) {
                        if (shipsPlaced < 5)
                            gameSession->getPlayer()->renderPlace(0, 0, ts, row, col, this->horizontal);
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
                        shipsPlaced = gameSession->getPlayer()->undoPlace();
                    }
            ));

    elements.push_back(
            doneBtn = std::make_shared<Button>(
                    height,
                    height - 60,
                    controlRoom,
                    20,
                    parent->font,
                    "Done",
                    0,
                    0xFF7F7F7F,
                    0xFFFFFFFF,
                    0xFF000000,
                    [=](Button* button) {
                        if (shipsPlaced == 5) {
                            if (gameSession->getGameState() == GameStateMachine::PLACE_SHIPS) {
                                gameSession->getPlayer()->freeze();
                                gameSession->transition(Battleship::Status::WAITING, 0, 0);
                                parent->setScreen(new SyncOpponentScreen(parent, gameSession));
                                return;
                            }
                        }
                    }
        ));

    elements.push_back(
            std::make_shared<Button>(
                    height,
                    height - 90,
                    controlRoom,
                    20,
                    parent->font,
                    "Cancel",
                    0,
                    0xFF7F7F7F,
                    0xFFFFFFFF,
                    0xFF000000,
                    [=](Button* button) {
                        parent->setScreen(new MainMenuScreen2(parent));
                    }
            ));
}

void PlaceShipsScreen2::onRender(float mouseX, float mouseY) {
    Screen::onRender(mouseX, mouseY);

    // calc room for controls on right
    float controlRoom = width - height;

    float ts = height / 5.5;

    if (shipsPlaced == 5) {
        board->setDisabled(true);
        doneBtn->setDisabled(false);
    } else {
        board->setDisabled(false);
        doneBtn->setDisabled(true);
    }

    glPushMatrix();
    glTranslatef(height, 0, 0);
    glScalef(.5, .5, 1);
    DrawableHelper::drawCenteredString(parent->font, "Place your ships", controlRoom, 20, 0xFFFFFFFF);
    DrawableHelper::drawString(parent->font, "Current Ship: ", 0, ts, 0xFFFFFFFF);
    if (shipsPlaced < 5) {
        DrawableHelper::drawCenteredString(
                parent->font,
                Battleship::SHIP_NAMES[shipsPlaced],
                controlRoom,
                ts + 30,
                0xFFFFFFFF
        );
    }
    glPopMatrix();
}

void PlaceShipsScreen2::placeShip(BoardElement2* element, int row, int col) {
    bool success = gameSession->getPlayer()->placeShip(col, row, Battleship::SHIP_LENGTHS[shipsPlaced], horizontal);
    if (success) {
        ++shipsPlaced;
    }
}