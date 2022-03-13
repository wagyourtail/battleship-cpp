//
// Created by william on 3/8/22.
//

#include "wagyourgui/elements/Button.h"
#include "battleship/screen/MainMenuScreen.h"
#include "battleship/NoGuiRunner.h"
#include "battleship/BSBot.h"
#include "battleship/BSPlayer.h"
#include "wagyourgui/GLFWSession.h"
#include "wagyourgui/Screen.h"
#include <cstring>

int main(int argc, char *argv[]) {
    NoGuiRunner* gamerunner;
    if (argc == 2 && strcmp("-nogui", argv[1]) == 0) {
        gamerunner = new NoGuiRunner(new BSPlayer(), new BSBot());
        gamerunner->runGame();
    } else {
        GLFWSession session{[](GLFWSession *session1) {
            Screen *screen = new MainMenuScreen(session1);
            return screen;
        }};
        session.runLoop();
    }
}
