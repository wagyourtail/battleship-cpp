//
// Created by william on 3/10/22.
//

#include "PlaceShipsScreen.h"
#include "battleship/screen/elements/BoardElement.h"
#include "wagyourgui/GLFWSession.h"


void PlaceShipsScreen::init(Window *window) {
    float ts;
    ts = height / 11;
    elements.push_back(new BoardElement(0, 0, ts * 11, session->font, gameSession->player, [=] (BoardElement *element, int row, int col, int button) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            this->placeShip(element, row, col);
        } else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
            this->horizontal = !this->horizontal;
        }
    }, [=] (BoardElement *element, int row, int col) {
        this->renderHover(element, row, col);
    }));
}

void PlaceShipsScreen::onRender(float mouseX, float mouseY) {
    Screen::onRender(mouseX, mouseY);
}

void PlaceShipsScreen::placeShip(BoardElement *element, int row, int col) {
    bool success = gameSession->player->placeShip({col, row, Battleship::SHIP_LENGTHS[shipsPlaced], horizontal});
    if (success) {
        shipsPlaced++;
    }
    if (shipsPlaced == 5) {
        //TODO: move to next screen
    }
}

void PlaceShipsScreen::renderHover(BoardElement *element, int row, int col) {

}