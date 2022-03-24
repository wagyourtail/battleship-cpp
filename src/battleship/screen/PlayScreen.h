//
// Created by william on 3/15/22.
//

#ifndef BATTLESHIP_PLAYSCREEN_H
#define BATTLESHIP_PLAYSCREEN_H


#include "src/wagyourgui/Screen.h"

#include <utility>
#include <chrono>
#include "src/battleship/GameSession.h"
#include "src/battleship/screen/elements/BoardElement.h"

class PlayScreen : public Screen {
    protected:
        std::shared_ptr<GameSession> gameSession;
        std::shared_ptr<BoardElement> board;
        GameState currentState{PLAYER_TURN};
        std::chrono::system_clock::time_point stateChangeTime = std::chrono::system_clock::now();
        std::chrono::system_clock::time_point lastStateChangeTime = std::chrono::system_clock::now();

    public:
        PlayScreen(GLFWSession* session, std::shared_ptr<GameSession> gameSession) :
                Screen(session), gameSession(std::move(gameSession)) {};
        void init(Window* window) override;
        void onRender(float mouseX, float mouseY) override;

    private:
        void handleAttack(int col, int row);
};


#endif //BATTLESHIP_PLAYSCREEN_H
