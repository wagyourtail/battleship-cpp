//
// Created by william on 3/10/22.
//

#include "PlaceShipsScreen.h"
#include "battleship/screen/elements/BoardElement.h"
#include "wagyourgui/GLFWSession.h"

void PlaceShipsScreen::init(Window *window) {
    float ts, i, j;
    ts = height / 11;
    elements.push_back(new BoardElement(0, 0, ts * 11, session->font, gameSession->player, [] (BoardElement *element, int row, int col) {
        std::cout << "Clicked on " << row << " " << col << std::endl;
    }));

}

void PlaceShipsScreen::onRender(float mouseX, float mouseY) {
    Screen::onRender(mouseX, mouseY);
}