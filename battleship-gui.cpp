//
// Created by william on 3/8/22.
//

#include "battleship-gui.h"
#include <cstring>

int main(int argc, char *argv[]) {
    GameRunner* gamerunner;
    if (argc == 2 && strcmp("-nogui", argv[1]) == 0) {
        gamerunner = new GameRunner(new BSPlayer(), new BSBot());
    } else {
        gamerunner = new GameRunnerGui(new BSPlayer(), new BSBot());
    }

    gamerunner->runGame();

}

void GameRunnerGui::runGame() {
    GLFWSession session{[] (GLFWSession *session1) {
        Screen *screen = new MainMenuScreen(session1);
        return  screen;
    }};
    session.runLoop();
}

void MainMenuScreen::init(Window *window) {

}

void MainMenuScreen::onRender(float mouseX, float mouseY) {
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    session->font->drawString("Hello, World!", 0, 10);
    Screen::onRender(mouseX, mouseY);
}
