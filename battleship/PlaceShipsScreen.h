//
// Created by william on 3/10/22.
//

#ifndef BATTLESHIP_PLACESHIPSSCREEN_H
#define BATTLESHIP_PLACESHIPSSCREEN_H


#include "../wagyourgui/Screen.h"
#include "GameSession.h"

class PlaceShipsScreen : public Screen {
    protected:
        GameSession *gameSession;
    public:
        PlaceShipsScreen(GLFWSession *session, GameSession *gameSession) : Screen(session), gameSession(gameSession) {}
        void init(Window *window) override;
};


#endif //BATTLESHIP_PLACESHIPSSCREEN_H