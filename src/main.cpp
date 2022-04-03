//
// Created by william on 3/8/22.
//

#include "wagyourgui/GLFWSession.h"
#include "wagyourgui/Screen.h"
#include "battleship/screen2/MainMenuScreen2.h"

int main(int argc, char* argv[]) {
    GLFWSession session{
            [](GLFWSession* session1) {
                Screen* screen = new MainMenuScreen2(session1);
                return screen;
            }};
    session.runLoop();
}

