//
// Created by william on 4/3/22.
//

#ifndef BATTLESHIP_PLACESHIPSCREEN2_H
#define BATTLESHIP_PLACESHIPSCREEN2_H


#include "wagyourgui/Screen.h"
#include "battleship/GameStateMachine.h"
#include "battleship/screen2/elements/BoardElement2.h"
#include "wagyourgui/elements/Button.h"

class PlaceShipsScreen2 : public Screen {
    protected:
        std::shared_ptr<BoardElement2> board;
        std::shared_ptr<Button> doneBtn;
        std::shared_ptr<GameStateMachine> gameSession;
        int shipsPlaced = 0;
        bool horizontal = true;
    public:
        PlaceShipsScreen2(GLFWSession* session, std::shared_ptr<GameStateMachine> gameSession) :
                Screen(session), gameSession(std::move(gameSession)) {}

        void init(Window* window) override;
        void onRender(float mouseX, float mouseY) override;

    private:
        void placeShip(BoardElement2* element, int row, int col);
};



#endif //BATTLESHIP_PLACESHIPSCREEN2_H
