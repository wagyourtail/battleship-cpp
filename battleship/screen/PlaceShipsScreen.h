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
        std::unique_ptr<GameSession> gameSession;
        int shipsPlaced = 0;
        bool horizontal = true;
    public:
        PlaceShipsScreen(GLFWSession *session, std::unique_ptr<GameSession> gameSession) : Screen(session), gameSession(std::move(gameSession)) {}
        void init(Window *window) override;
        void onRender(float mouseX, float mouseY) override;

    private:
        void placeShip(BoardElement *element, int row, int col);
};


#endif //BATTLESHIP_PLACESHIPSSCREEN_H
