//
// Created by william on 3/10/22.
//

#include "PlaceShipsScreen.h"

void PlaceShipsScreen::init(Window *window) {
    if (width < height) {
        ts = width / 12;
        i = ts;
        j = ts;
    } else {
        ts = height / 12;
        i = ts;
        j = ts;
    }
}

void PlaceShipsScreen::onRender(float mouseX, float mouseY) {

    gameSession->player->render(i, j, ts);
}