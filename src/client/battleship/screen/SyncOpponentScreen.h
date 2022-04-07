//
// Created by william on 4/3/22.
//

#ifndef BATTLESHIP_SYNCOPPONENTSCREEN_H
#define BATTLESHIP_SYNCOPPONENTSCREEN_H


#include "client/wagyourgui/Screen.h"
#include "client/battleship/GameStateMachine.h"

class SyncOpponentScreen : public Screen {
    protected:
        std::shared_ptr<GameStateMachine> gameSession;
    public:
        SyncOpponentScreen(GLFWSession* session, std::shared_ptr<GameStateMachine> gameSession) :
                Screen(session), gameSession(std::move(gameSession)) {}

        void init(Window* window) override;
        void onRender(float mouseX, float mouseY) override;
};


#endif //BATTLESHIP_SYNCOPPONENTSCREEN_H
