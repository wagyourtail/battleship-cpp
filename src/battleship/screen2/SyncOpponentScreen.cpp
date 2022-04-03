//
// Created by william on 4/3/22.
//

#include "SyncOpponentScreen.h"
#include "wagyourgui/GLFWSession.h"
#include "wagyourgui/DrawableHelper.h"
#include "wagyourgui/elements/Button.h"
#include "MainMenuScreen2.h"
#include "PlayScreen2.h"

using namespace DrawableHelper;

void SyncOpponentScreen::init(Window* window) {
    elements.push_back(
            std::make_shared<Button>(
                    height / 2 + 20,
                    width / 2 - 100,
                    200,
                    50,
                    parent->font,
                    "Cancel",
                    0,
                    0xFF7F7F7F,
                    0xFFFFFFFF,
                    0xFF000000,
                    [=](Button* button) {
                        parent->setScreen(new MainMenuScreen2(parent));
                    }
            ));
}

void SyncOpponentScreen::onRender(float mouseX, float mouseY) {
    gameSession->poll();

    if (gameSession->getGameState() == GameStateMachine::PLAYER_TURN || gameSession->getGameState() == GameStateMachine::ACK_OPPONENT_TURN) {
        parent->setScreen(new PlayScreen2(parent, gameSession));
    }

    drawCenteredString(parent->font, "Waiting for Opponent to Place ships", width / 2, height / 2, 0xFFFFFFFF);

    Screen::onRender(mouseX, mouseY);
}