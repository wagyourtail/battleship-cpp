//
// Created by william on 3/1/22.
//

#include "battleship-nogui.h"

Status BSLocal::attackedAt(int x, int y) {
    // space already hit
    if (board[x][y] & 1) {
        return Status::ERROR;
    }

    board[x][y] |= 1;

    // hit
    if (board[x][y] & 2) {
        int sc = sunkCheck(x, y);
        --numSpacesAlive;

        if (numSpacesAlive == 0) {
            return Status::GAME_END;
        }

        if (sc == 0) return Status::HIT;

        switch (sc) {
            case 2:
                return Status::SUNK_2;
            case 3:
                return Status::SUNK_3;
            case 4:
                return Status::SUNK_4;
            case 5:
                return Status::SUNK_5;
            default:
                return Status::ERROR;
        }
        return Status::HIT;
    }
    return Status::MISS;
}

int BSLocal::sunkCheck(int x, int y) {
    int shipid = board[x][y] >> 2;

    // no ship so always false
    if (shipid == 0) {
        return 0;
    }

    int l = 0;
    bool horizontal = false;
    if (x > 0 && board[x-1][y] >> 2 == shipid) {
        // go to left end
        while (board[--x][y] >> 2 == shipid) {}
        horizontal = true;
    } else if (x < 9 && board[x+1][y] >> 2 == shipid) {
        // already at left end
        --x;
        horizontal = true;
    } else if (y > 0 && board[x][y-1] >> 2 == shipid) {
        // go to top
        while (board[x][--y] >> 2 == shipid) {}
    } else if (y < 9 && board[x][y+1] >> 2 == shipid) {
        // already at top
        --y;
    } else {
        return 0;
    }

    int boardspot;
    if (horizontal) {
        // go to right end
        while ((boardspot = board[++x][y]) >> 2 == shipid) {
            ++l;
            if (!(boardspot & 1)) {
                return 0;
            }
        }
    } else {
        // go to bottom
        while ((boardspot = board[x][++y]) >> 2 == shipid) {
            ++l;
            if (!(boardspot & 1)) {
                return 0;
            }
        }
    }
    return l - 1;
}

Status BSLocal::attack(int x, int y) {
    Status status = opponent->attackedAt(x, y);
    switch (status) {
        case Status::ERROR:
            return Status::ERROR;
        case Status::SUNK_2:
        case Status::SUNK_3:
        case Status::SUNK_4:
        case Status::SUNK_5:
        case Status::HIT:
            hitBoard[x][y] |= 3;
            return status;
        case Status::MISS:
            hitBoard[x][y] |= 1;
            return Status::MISS;
        case Status::GAME_END:
            return Status::GAME_END;
    }
    return Status::ERROR;
}

bool BSLocal::placeShip(Ship ship) {
    int sid = ++numShips;
    sid <<= 2;
    sid |= 2;
    if (ship.horizontal) {
        for (int i = ship.x; i < ship.x + ship.length; ++i) {
            if (board[i][ship.y] >> 2 != 0 || i > 9 || i < 0) {
                return false;
            }
        }
        for (int i = ship.x; i < ship.x + ship.length; ++i) {
            board[i][ship.y] = sid;
        }
    } else {
        for (int i = ship.y; i < ship.y + ship.length; ++i) {
            if (board[ship.x][i] >> 2 != 0 || i > 9 || i < 0) {
                return false;
            }
        }
        for (int i = ship.y; i < ship.y + ship.length; ++i) {
            board[ship.x][i] = sid;
        }
    }
    numSpacesAlive += ship.length;
    return true;
}

void BSLocal::placeRandomShip(int length) {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 9);
    int x, y;
    bool horizontal;
    do {
        x = dist(rd);
        y = dist(rd);
        horizontal = dist(rd) % 2;
    } while (!placeShip({x, y, length, horizontal}));
}

void BSPlayer::render() {
    std::string hit = "\033[31m⬛\033[0m";
    std::string miss = "\033[30;1m⬛\033[0m";
    std::string none = "\033[37m⬜\033[0m";

    std::string ansi_background_reset = "\033[0m";
    std::string ansi_background_gray = "\033[100m";

    std::cout << "hit: " << hit << ", miss: " << miss << ", none: " << none << std::endl;
    std::cout << std::endl;
    std::cout << "   ａ ｂ ｃ ｄ ｅ ｆ ｇ ｈ ｉ ｊ" << std::endl;
    for (int y = 0; y < 10; ++y) {
        std::cout << y + 1 << " ";
        if (y != 9) {
            std::cout << " ";
        }
        for (int x = 0; x < 10; ++x) {
            if (board[x][y] & 1) {
                if (board[x][y] & 2) {
                    std::cout << ansi_background_gray << hit << ansi_background_reset;
                } else {
                    std::cout << miss;
                }
            } else {
                if (board[x][y] & 2) {
                    std::cout << ansi_background_gray << none << ansi_background_reset;
                } else {
                    std::cout << none;
                }
            }
            if (x < 9) {
                if (board[x+1][y] >> 2 == board[x][y] >> 2 && board[x+1][y] >> 2 != 0) {
                    std::cout << ansi_background_gray << " " << ansi_background_reset;
                } else {
                    std::cout << " ";
                }
            }
        }
        std::cout << std::endl;
        if (y < 9) {
            std::cout << "   ";
            for (auto & x : board) {
                if (x[y+1] >> 2 == x[y] >> 2 && x[y+1] >> 2 != 0) {
                    std::cout << ansi_background_gray << "　" << ansi_background_reset << " ";
                } else {
                    std::cout << "　 ";
                }
            }
            std::cout << std::endl;
        }
    }
}

void BSPlayer::renderHitBoard() {
    std::string hit = "\033[31m⬛\033[0m";
    std::string miss = "\033[30;1m⬛\033[0m";
    std::string none = "\033[37m⬜\033[0m";

    std::cout << "hit: " << hit << ", miss: " << miss << ", none: " << none << std::endl;
    std::cout << std::endl;
    std::cout << "    ａ ｂ ｃ ｄ ｅ ｆ ｇ ｈ ｉ ｊ" << std::endl;
    for (int y = 0; y < 10; ++y) {
        std::cout << y + 1 << "  ";
        if (y != 9) {
            std::cout << " ";
        }
        for (int x = 0; x < 10; ++x) {
            if (hitBoard[x][y] & 1) {
                if (hitBoard[x][y] & 2) {
                    std::cout << hit;
                } else {
                    std::cout << miss;
                }
            } else {
                std::cout << none;
            }
            if (x < 9) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
        if (y < 9) {
            std::cout << "   ";
            for (auto & x : hitBoard) {
                std::cout << "　 ";
            }
            std::cout << std::endl;
        }
    }
}

void BSPlayer::promptShipPlacement(int length) {
    bool placed = false;
    do {
        std::cout << "Your board:" << std::endl;
        render();
        std::cout << "Place your " << length << " unit ship." << std::endl;
        std::cout << "Enter the coordinates of the top/left of the ship. or 'r' for random" << std::endl;
        std::cout << "Example: a1" << std::endl;
        std::string input;
        std::cin >> input;
        if (input.length() != 2 && input.substr(1) != "10") {
            if (input == "r") {
                placeRandomShip(length);
                placed = true;
            } else {
                std::cout << "Invalid input" << std::endl;
            }
            continue;
        }
        int x = input[0] - 'a';
        if (input[1] < '0' || input[1] > '9') {
            std::cout << "Invalid input" << std::endl;
            continue;
        }
        int y = std::stoi(input.substr(1)) - 1;
        if (x < 0 || x > 9 || y < 0 || y > 9) {
            std::cout << "Invalid input." << std::endl;
            continue;
        }
        std::cout << "Enter the direction of the ship. (h for horizontal, v for vertical)" << std::endl;
        char dir;
        std::cin >> dir;
        if (dir != 'h' && dir != 'v') {
            std::cout << "Invalid input." << std::endl;
            continue;
        }
        placed = placeShip({x, y, length, dir == 'h'});
        if (!placed) {
            std::cout << "Invalid placement. either out of board or overlapping" << std::endl;
        }
    } while (!placed);
}

Status BSPlayer::runTurn() {
    std::cout << "Your turn." << std::endl;
    while (true) {
        std::cout << "Enter the coordinates of the shot. or 'r' for random" << std::endl;
        std::cout << "Example: a1" << std::endl;
        std::string input;
        std::cin >> input;
        if (input == "r") {
            std::random_device rd;
            std::uniform_int_distribution<int> dist(0, 9);
            int x, y;
            do {
                x = dist(rd);
                y = dist(rd);
            } while (hitBoard[x][y] & 1);
            return BSLocal::attack(x, y);
        }
        if (input.length() != 2 && input.substr(1) != "10") {
            std::cout << "Invalid input" << std::endl;
            continue;
        }
        int x = input[0] - 'a';
        if (input[1] < '0' || input[1] > '9') {
            std::cout << "Invalid input" << std::endl;
            continue;
        }
        int y = std::stoi(input.substr(1)) - 1;
        if (x < 0 || x > 9 || y < 0 || y > 9) {
            std::cout << "Invalid input." << std::endl;
            continue;
        }
        return BSLocal::attack(x, y);
    }
}

void GameRunner::runGame() {
    std::cout << "Welcome to Battleship!" << std::endl;
    std::cout << "Place your ships!" << std::endl;
    player->setup();
    opponent->setup();
    std::cout << "Your board:" << std::endl;
    player->render();
    std::cout << "prepare to battle!" << std::endl;
    // select starting player
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 1);
    int start = dist(rd);
    if (start == 0) {
        std::cout << "You start." << std::endl;
    } else {
        std::cout << "Opponent starts." << std::endl;
    }
    // run game
    while (true) {
        if (start == 0) {
            player->renderHitBoard();
            switch (player->runTurn()) {
                case HIT:
                    std::cout << "Hit!" << std::endl;
                    break;
                case MISS:
                    std::cout << "Miss." << std::endl;
                    break;
                case SUNK_2:
                case SUNK_3:
                case SUNK_4:
                case SUNK_5:
                    std::cout << "Sunk!" << std::endl;
                    break;
                case GAME_END:
                    std::cout << "You win!" << std::endl;
                    return;
                case ERROR:
                    std::cout << "An error has occured, try again..." << std::endl;
                    continue;
            }
            start = 1;
        } else {
            switch (opponent->runTurn()) {
                case HIT:
                    std::cout << "Hit!" << std::endl;
                    break;
                case MISS:
                    std::cout << "Miss." << std::endl;
                    break;
                case SUNK_2:
                case SUNK_3:
                case SUNK_4:
                case SUNK_5:
                    std::cout << "Sunk!" << std::endl;
                    break;
                case GAME_END:
                    std::cout << "You lose!" << std::endl;
                    return;
                case ERROR:
                    std::cout << "An error has occured, trying again..." << std::endl;
                    continue;
            }
            start = 0;
            player->render();
        }
    }
}


Status BSBot::runTurn() {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 9);
    int x, y;
    do {
        x = dist(rd);
        y = dist(rd);
    } while (hitBoard[x][y] & 1);
    return BSLocal::attack(x, y);
}