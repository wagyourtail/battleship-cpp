//
// Created by william on 4/3/22.
//

#include "SyncOpponentScreen.h"
#include "client/wagyourgui/GLFWSession.h"
#include "client/wagyourgui/DrawableHelper.h"
#include "client/wagyourgui/elements/Button.h"
#include "MainMenuScreen.h"
#include "PlayScreen.h"

using namespace DrawableHelper;

void SyncOpponentScreen::init(Window* window) {
    elements.push_back(
            std::make_shared<Button>(
                    width / 2 - 100,
                    height / 2 + 50,
                    200,
                    50,
                    parent->font,
                    "Cancel",
                    0,
                    0xFF7F7F7F,
                    0xFFFFFFFF,
                    0xFF000000,
                    [=](Button* button) {
                        parent->setScreen(new MainMenuScreen(parent));
                    }
            ));
}

void SyncOpponentScreen::onRender(float mouseX, float mouseY) {
    gameSession->poll();

    if (gameSession->getGameState() == GameStateMachine::PLAYER_TURN ||
            gameSession->getGameState() == GameStateMachine::ACK_OPPONENT_TURN) {
        parent->setScreen(new PlayScreen(parent, gameSession));
        return;
    }

    drawCenteredString(parent->font, "Waiting for Opponent to Place ships", width / 2, height / 2, 0xFFFFFFFF);

    Screen::onRender(mouseX, mouseY);
}