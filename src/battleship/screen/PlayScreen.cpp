//
// Created by william on 3/15/22.
//

#include "PlayScreen.h"
#include "src/wagyourgui/GLFWSession.h"
#include "src/wagyourgui/GLBuilder.h"
#include "src/wagyourgui/DrawableHelper.h"
#include "WinLossScreen.h"
#include "src/wagyourgui/elements/Button.h"

void PlayScreen::init(Window* window) {
    float ts = height / 11;
    elements.push_back(
            board = std::make_shared<BoardElement>(
                    0,
                    0,
                    ts * 11,
                    parent->font,
                    gameSession->player,
                    [=](BoardElement* element, int row, int col, int button) {
                        if (button == GLFW_MOUSE_BUTTON_LEFT) {
                            handleAttack(col, row);
                        }
                    },
                    [=](BoardElement* element, int row, int col) {
                        Battleship::atlas.bind();
                        GLBuilder& builder = GLBuilder::getImmediate();
                        builder.begin(GL_TRIANGLE_STRIP, GLBuilder::POS_COL_TEX)
                               .color(gameSession->player->isHit(col, row) ? 0xFFFF0000 : 0xFFFFFFFF)
                               .vertex((1 + col) * ts, (1 + row) * ts).uv(48, 16, 80, 64).next()
                               .vertex((1 + col) * ts, (2 + row) * ts).uv(48, 32, 80, 64).next()
                               .vertex((2 + col) * ts, (1 + row) * ts).uv(64, 16, 80, 64).next()
                               .vertex((2 + col) * ts, (2 + row) * ts).uv(64, 32, 80, 64).next()
                               .end();
                    }
            ));

    // calc room for controls on right
    float controlRoom = width - height;

    elements.push_back(
            std::make_shared<Button>(
                    height,
                    height - 30,
                    controlRoom,
                    20,
                    parent->font,
                    "Surrender",
                    0,
                    0xFF7F7F7F,
                    0xFFFFFFFF,
                    0xFF000000,
                    [=](Button* button) {
                        gameSession->surrender();
                        parent->setScreen(new WinLossScreen(parent, "You Lose!"));
                    }
            ));


    currentState = gameSession->getState();
    board->setRenderHitBoard(gameSession->getState() == PLAYER_TURN);
}

void PlayScreen::onRender(float mouseX, float mouseY) {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    if (gameSession->getState() == GAME_OVER) {
        if (currentState == PLAYER_TURN) {
            // win
            parent->setScreen(new WinLossScreen(parent, "You Win!"));
        } else {
            // lose
            parent->setScreen(new WinLossScreen(parent, "You Lose!"));
        }
        return;
    }

    if (currentState == OPPONENT_TURN) {
        int count = std::chrono::duration_cast<std::chrono::seconds>(now - lastStateChangeTime).count();
        if (count > 2) {
            gameSession->pollOpponent();
        }
    }

    if (currentState != gameSession->getState()) {
        int count = std::chrono::duration_cast<std::chrono::seconds>(now - stateChangeTime).count();
        if (count > 1) {
            board->setRenderHitBoard(gameSession->getState() == PLAYER_TURN);
            board->setDisabled(gameSession->getState() != PLAYER_TURN);
            currentState = gameSession->getState();
            lastStateChangeTime = now;
            stateChangeTime = now;
        }
    } else {
        stateChangeTime = now;
    }


    Screen::onRender(mouseX, mouseY);

    // calc room for controls on right
    float controlRoom = width - height;

    std::string titleText;

    switch (currentState) {
        case PLACE_SHIPS:
        case GAME_OVER:
            throw std::runtime_error("bad state for screen");
        case PLAYER_TURN:
            titleText = "Your turn";
            break;
        case OPPONENT_TURN:
            titleText = "Opponent's turn";
            break;
    }
    glPushMatrix();
    glTranslatef(height, 0, 0);
    glScalef(.5, .5, 1);
    DrawableHelper::drawCenteredString(parent->font, titleText, controlRoom, 20, 0xFFFFFFFF);
    glPopMatrix();
}

void PlayScreen::handleAttack(int col, int row) {
    if (gameSession->getState() == PLAYER_TURN) {
        gameSession->attack(col, row);
    }
}