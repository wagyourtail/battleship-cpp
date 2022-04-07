//
// Created by william on 4/6/22.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory>
#include "ConnectingScreen.h"
#include "client/wagyourgui/GLFWSession.h"
#include "client/wagyourgui/DrawableHelper.h"
#include "MainMenuScreen2.h"
#include "PlaceShipScreen2.h"

std::string ConnectingScreen::IP = "127.0.0.1";
int ConnectingScreen::PORT = 5549;

ConnectingScreen::ConnectingScreen(GLFWSession* parent) : Screen(parent) {
    int sock;
    sockaddr_in dest;

    dest.sin_family = AF_INET;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock < 0) {
        perror("socket");
        parent->setScreen(new MainMenuScreen2(parent));
        return;
    }

    dest.sin_port = htons(PORT);
    dest.sin_addr.s_addr = inet_addr(IP.c_str());

    if (connect(sock, (sockaddr*)&dest, sizeof(dest)) < 0) {
        perror("connect");
        parent->setScreen(new MainMenuScreen2(parent));
        return;
    }

    connection = std::make_shared<RemoteOpponent>(sock);

    connection->connectionThread = std::thread(&ConnectingScreen::waitForReadHost, this, connection);

    *connection->connection << "h";
}

ConnectingScreen::ConnectingScreen(GLFWSession* parent, const std::string& joincode) : Screen(parent) {
    int sock;
    sockaddr_in dest{};

    dest.sin_family = AF_INET;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock < 0) {
        perror("socket");
        parent->setScreen(new MainMenuScreen2(parent));
        return;
    }

    dest.sin_port = htons(PORT);
    dest.sin_addr.s_addr = inet_addr(IP.c_str());

    if (connect(sock, (sockaddr*)&dest, sizeof(dest)) < 0) {
        perror("connect");
        parent->setScreen(new MainMenuScreen2(parent));
        return;
    }

    connection = std::make_shared<RemoteOpponent>(sock);

    connection->connectionThread = std::thread(&ConnectingScreen::waitForReadClient, this, connection);

    *connection->connection << ("j" + joincode);
}

void ConnectingScreen::waitForReadHost(std::shared_ptr<RemoteOpponent> connection) {
    std::string message;
    *connection->connection >> message;
    if (connection->connection->fail()) {
        parent->setScreen(new MainMenuScreen2(parent));
        return;
    }
    if (message.length() == 6 && message[0] == 's') {
        this->message.push_back("Join Code: " + message.substr(1));
        // ide told me to use this, i assume it's a std::move thing
        this->message.emplace_back("Waiting for opponent...");

        message = "";
        *connection->connection >> message;
        if (connection->connection->fail()) {
            parent->setScreen(new MainMenuScreen2(parent));
            return;
        }
    } else {
        parent->setScreen(new MainMenuScreen2(parent));
        return;
    }

    if (message.length() == 2 && message[0] == 's') {
        if (message[1] == '1') {
            connection->gf = true;
        } else {
            connection->gf = false;
        }
    } else {
        parent->setScreen(new MainMenuScreen2(parent));
        return;
    }

    parent->setScreen(new PlaceShipsScreen2(parent, std::make_shared<GameStateMachine>(std::make_shared<BSPlayer2>(), connection)));
    connection->beginMainGameReadTask();
}

void ConnectingScreen::waitForReadClient(std::shared_ptr<RemoteOpponent> connection) {
    std::string message;
    *connection->connection >> message;
    if (connection->connection->fail()) {
        parent->setScreen(new MainMenuScreen2(parent));
        return;
    }
    if (message.length() == 2 && message[0] == 's') {
        if (message[1] == '1') {
            connection->gf = true;
        } else {
            connection->gf = false;
        }
    } else {
        parent->setScreen(new MainMenuScreen2(parent));
        return;
    }

    parent->setScreen(new PlaceShipsScreen2(parent, std::make_shared<GameStateMachine>(std::make_shared<BSPlayer2>(), connection)));
    connection->beginMainGameReadTask();
}

void ConnectingScreen::init(Window* window) {
    addElement(std::make_shared<Button>(
            5, height - 35, width / 2 - 10, 20,
            parent->font, "Cancel", 0, 0xFF4f4f4f, 0xFFFFFFFF, 0xFF000000,
            [=](Button* b) {
                parent->setScreen(new MainMenuScreen2(parent));
            }
    ));
}

using namespace DrawableHelper;

void ConnectingScreen::onRender(float mouseX, float mouseY) {
    int y = 10;
    for (auto& i : message) {
        drawCenteredString(parent->font, i, width / 2, y, 0xFFFFFFFF);
        y += 25;
    }
    Screen::onRender(mouseX, mouseY);
}

