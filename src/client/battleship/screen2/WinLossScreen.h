//
// Created by william on 3/22/22.
//

#include <string>
#include "client/wagyourgui/GLFWSession.h"
#include "client/wagyourgui/Screen.h"
#include "client/wagyourgui/DrawableHelper.h"
#include "MainMenuScreen2.h"

class WinLossScreen : public Screen {
        std::string message;

    public:
        WinLossScreen(GLFWSession* parent, std::string message) : Screen(parent), message(std::move(message)) {}

        bool onClick(float x, float y, int button) override {
            parent->setScreen(new MainMenuScreen2(parent));
            return true;
        }

        void onRender(float mouseX, float mouseY) override {
            DrawableHelper::drawCenteredString(parent->font, message, width / 2, height / 2, 0xFFFFFFFF);

            glPushMatrix();
            glTranslatef(width / 2, height / 2 + parent->font->FONT_HEIGHT + 4, 0);
            glScalef(0.5, 0.5, 1);
            DrawableHelper::drawCenteredString(parent->font, "Click to continue", 0, 0, 0xFFFFFFFF);
            glPopMatrix();
        }

        void init(Window* window) override {}
};