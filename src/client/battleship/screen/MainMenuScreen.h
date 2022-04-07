//
// Created by william on 4/3/22.
//

#ifndef BATTLESHIP_MAINMENUSCREEN2_H
#define BATTLESHIP_MAINMENUSCREEN2_H


#include "client/wagyourgui/Screen.h"

class MainMenuScreen : public Screen {
    public:
        explicit MainMenuScreen(GLFWSession* session) : Screen(session) {};
        void init(Window* window) override;

        void onRender(float mouseX, float mouseY) override;
};


#endif //BATTLESHIP_MAINMENUSCREEN2_H
