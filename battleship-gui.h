//
// Created by william on 3/8/22.
//

#ifndef BATTLESHIP_CPP_BATTLESHIP_GUI_H
#define BATTLESHIP_CPP_BATTLESHIP_GUI_H

#include "battleship-nogui.cpp"
#include "wagyourgui/GLFWSession.h"
#include "wagyourgui/Texture.h"

class GameRunnerGui : public GameRunner {
public:
    GameRunnerGui(BSPlayer* player, BSOpponent* opponent) : GameRunner(player, opponent) {};
    void runGame() override;
};

class MainMenuScreen : public Screen {
        Texture test{"texture_atlas.png"};
    public:
        explicit MainMenuScreen(GLFWSession *session) : Screen(session) {};
        void init(Window *window) override;

        void onRender(float mouseX, float mouseY) override;
};

#endif //BATTLESHIP_CPP_BATTLESHIP_GUI_H
