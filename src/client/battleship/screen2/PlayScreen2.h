//
// Created by william on 4/3/22.
//

#ifndef BATTLESHIP_PLAYSCREEN2_H
#define BATTLESHIP_PLAYSCREEN2_H

#include <utility>
#include "client/battleship/GameStateMachine.h"
#include "client/battleship/screen2/elements/BoardElement2.h"
#include "client/wagyourgui/Screen.h"

class PlayScreen2 : public Screen {
    protected:
        std::shared_ptr<GameStateMachine> gameSession;
        std::shared_ptr<BoardElement2> board;
    public:
        PlayScreen2(GLFWSession* session, std::shared_ptr<GameStateMachine> gameSession) :
                Screen(session), gameSession(std::move(gameSession)) {};
        void init(Window* window) override;
        void onRender(float mouseX, float mouseY) override;

    private:
        void handleAttack(int col, int row);
};

#endif //BATTLESHIP_PLAYSCREEN2_H
