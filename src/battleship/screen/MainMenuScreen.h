//
// Created by william on 3/10/22.
//

#ifndef BATTLESHIP_MAINMENUSCREEN_H
#define BATTLESHIP_MAINMENUSCREEN_H

#include "src/wagyourgui/Screen.h"
#include "src/wagyourgui/Texture.h"

class MainMenuScreen : public Screen {
    public:
        explicit MainMenuScreen(GLFWSession *session) : Screen(session) {};
        void init(Window *window) override;

        void onRender(float mouseX, float mouseY) override;
};

#endif //BATTLESHIP_MAINMENUSCREEN_H
