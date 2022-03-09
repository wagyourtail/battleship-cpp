//
// Created by william on 3/8/22.
//

#include "battleship-gui.h"
#include "string.h"

int main(int argc, char *argv[]) {
    GameRunner* gamerunner;
    if (argc == 2) {
        if (strcmp("-nogui", argv[1]) == 0) {
            gamerunner = new GameRunner(new BSPlayer(), new BSBot());
        }
    }


}