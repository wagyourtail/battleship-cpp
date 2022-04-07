//
// Created by william on 4/3/22.
//

#ifndef BATTLESHIP_PLACESHIPSCREEN2_H
#define BATTLESHIP_PLACESHIPSCREEN2_H


#include "client/wagyourgui/Screen.h"
#include "client/battleship/GameStateMachine.h"
#include "client/battleship/screen/elements/BoardElement.h"
#include "client/wagyourgui/elements/Button.h"

class PlaceShipsScreen : public Screen {
    protected:
        std::shared_ptr<BoardElement> board;
        std::shared_ptr<Button> doneBtn;
        std::shared_ptr<GameStateMachine> gameSession;
        int shipsPlaced = 0;
        bool horizontal = true;
    public:
        PlaceShipsScreen(GLFWSession* session, std::shared_ptr<GameStateMachine> gameSession) :
                Screen(session), gameSession(std::move(gameSession)) {}

        void init(Window* window) override;
        void onRender(float mouseX, float mouseY) override;

    private:
        void placeShip(BoardElement* element, int row, int col);
};


#endif //BATTLESHIP_PLACESHIPSCREEN2_H
