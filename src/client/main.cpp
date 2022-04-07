//
// Created by william on 3/8/22.
//

#include "client/wagyourgui/GLFWSession.h"
#include "client/wagyourgui/Screen.h"
#include "client/battleship/screen2/MainMenuScreen2.h"

int main(int argc, char* argv[]) {
    GLFWSession session{
            [](GLFWSession* session1) {
                Screen* screen = new MainMenuScreen2(session1);
                return screen;
            }};
    try {
        session.runLoop();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

