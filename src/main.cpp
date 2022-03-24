//
// Created by william on 3/8/22.
//

#include "src/battleship/screen/MainMenuScreen.h"
#include "src/battleship/NoGuiRunner.h"
#include "src/battleship/BSBot.h"
#include "src/battleship/BSPlayer.h"
#include "src/wagyourgui/GLFWSession.h"
#include "src/wagyourgui/Screen.h"
#include <cstring>

int main(int argc, char* argv[]) {
    NoGuiRunner* gamerunner;
    if (argc == 2 && strcmp("-nogui", argv[1]) == 0) {
        gamerunner = new NoGuiRunner(new BSPlayer(), new BSBot());
        gamerunner->runGame();
    } else {
        GLFWSession session{
                [](GLFWSession* session1) {
                    Screen* screen = new MainMenuScreen(session1);
                    return screen;
                }};
        session.runLoop();
    }
}

