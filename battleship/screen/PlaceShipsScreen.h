//
// Created by william on 3/10/22.
//

#ifndef BATTLESHIP_PLACESHIPSSCREEN_H
#define BATTLESHIP_PLACESHIPSSCREEN_H


#include "wagyourgui/Screen.h"
#include "battleship/GameSession.h"
#include "battleship/screen/elements/BoardElement.h"

class PlaceShipsScreen : public Screen {
    protected:
        GameSession *gameSession;
        int shipsPlaced = 0;
        bool horizontal = true;
    public:
        PlaceShipsScreen(GLFWSession *session, GameSession *gameSession) : Screen(session), gameSession(gameSession) {}
        void init(Window *window) override;
        void onRender(float mouseX, float mouseY) override;

    private:
        void renderHover(BoardElement *element, int row, int col);
        void placeShip(BoardElement *element, int row, int col);
};


#endif //BATTLESHIP_PLACESHIPSSCREEN_H
