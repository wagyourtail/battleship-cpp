//
// Created by william on 4/6/22.
//

#ifndef BATTLESHIP_SERVER_CONNECTINGSCREEN_H
#define BATTLESHIP_SERVER_CONNECTINGSCREEN_H


#include "client/wagyourgui/Screen.h"
#include "shared/SocketConnection.h"
#include "client/battleship/player2/RemoteOpponent.h"
#include <thread>

class ConnectingScreen : public Screen {
        static std::string IP;
        static int PORT;
        std::shared_ptr<RemoteOpponent> connection;
        std::vector<std::string> message{};
    public:
        ConnectingScreen(GLFWSession* parent, const std::string& joincode);
        explicit ConnectingScreen(GLFWSession* parent);

        void init(Window* window) override;

        void onRender(float mouseX, float mouseY) override;

    private:
        void waitForReadHost(std::shared_ptr<RemoteOpponent> connection);
        void waitForReadClient(std::shared_ptr<RemoteOpponent> connection);
};


#endif //BATTLESHIP_SERVER_CONNECTINGSCREEN_H
