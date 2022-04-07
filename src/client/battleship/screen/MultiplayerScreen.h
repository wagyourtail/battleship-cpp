//
// Created by william on 4/6/22.
//

#ifndef BATTLESHIP_SERVER_MULTIPLAYERSCREEN_H
#define BATTLESHIP_SERVER_MULTIPLAYERSCREEN_H


#include "client/wagyourgui/Screen.h"

class MultiplayerScreen : public Screen {
    public:
        explicit MultiplayerScreen(GLFWSession* session) : Screen(session) {};
        void init(Window* window) override;

        void onRender(float mouseX, float mouseY) override;
};


#endif //BATTLESHIP_SERVER_MULTIPLAYERSCREEN_H
