//
// Created by william on 4/3/22.
//

#include "client/wagyourgui/GLFWSession.h"
#include "PlayScreen.h"
#include "client/wagyourgui/GLBuilder.h"
#include "client/wagyourgui/elements/Button.h"
#include "WinLossScreen.h"

void PlayScreen::init(Window* window) {
    float ts = height / 11;
    elements.push_back(
            board = std::make_shared<BoardElement>(
                    0,
                    0,
                    ts * 11,
                    parent->font,
                    gameSession->getPlayer(),
                    [=](BoardElement* element, int row, int col, int button) {
                        if (button == GLFW_MOUSE_BUTTON_LEFT) {
                            handleAttack(col, row);
                        }
                    },
                    [=](BoardElement* element, int row, int col) {
                        Battleship::atlas.bind();
                        GLBuilder& builder = GLBuilder::getImmediate();
                        builder.begin(GL_TRIANGLE_STRIP, GLBuilder::POS_COL_TEX)
                               .color(gameSession->getPlayer()->attackBoardHit(col, row) ? 0xFFFF0000 : 0xFFFFFFFF)
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
                        gameSession->getOpponent()->surrender();
                        parent->setScreen(new WinLossScreen(parent, "You Lose!"));
                    }
            ));

    elements.push_back(
            std::make_shared<Button>(
                    height,
                    height - 60,
                    controlRoom,
                    20,
                    parent->font,
                    "Switch Board",
                    0,
                    0xFF7F7F7F,
                    0xFFFFFFFF,
                    0xFF000000,
                    [=](Button* button) {
                        board->setRenderHitBoard(!board->getRenderHitBoard());
                    }
            ));

    board->setRenderHitBoard(gameSession->getGameState() == GameStateMachine::PLAYER_TURN);
}

void PlayScreen::onRender(float mouseX, float mouseY) {
    gameSession->poll();

    board->setDisabled(gameSession->getGameState() != GameStateMachine::PLAYER_TURN || !board->getRenderHitBoard());

    // calc room for controls on right
    float controlRoom = width - height;
    std::string titleText;

    switch (gameSession->getGameState()) {
        case GameStateMachine::PLACE_SHIPS:
        case GameStateMachine::WAIT_FOR_OPPONENT_PLACE_SHIPS:
            gameSession->getOpponent()->surrender();
            parent->setScreen(new WinLossScreen(parent, "A critical error has occured!"));
            return;
        case GameStateMachine::PLAYER_TURN:
        case GameStateMachine::WAIT_FOR_OPPONENT_ACK:
            titleText = "Your Turn";
            break;
        case GameStateMachine::ACK_OPPONENT_TURN:
            titleText = "Opponent's Turn";
            break;
        case GameStateMachine::GAME_OVER:
            if (gameSession->getPlayer()->isLost()) {
                // lose
                parent->setScreen(new WinLossScreen(parent, "You Lose!"));
            } else {
                // win
                parent->setScreen(new WinLossScreen(parent, "You Win!"));
            }
            return;
    }

    glPushMatrix();
    glTranslatef(height, 0, 0);
    glScalef(.5, .5, 1);
    DrawableHelper::drawCenteredString(parent->font, titleText, controlRoom, 20, 0xFFFFFFFF);
    glPopMatrix();

    Screen::onRender(mouseX, mouseY);
}

void PlayScreen::handleAttack(int col, int row) {
    if (gameSession->getGameState() == GameStateMachine::PLAYER_TURN) {
        gameSession->transition(Battleship::WAITING, col, row);
    }
}