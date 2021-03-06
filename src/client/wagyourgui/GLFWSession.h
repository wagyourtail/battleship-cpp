//
// Created by william on 3/9/22.
//

#ifndef BATTLESHIP_GLFWSESSION_H
#define BATTLESHIP_GLFWSESSION_H


#include "Screen.h"
#include "Font.h"
#include "Window.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <chrono>
#include <functional>
#include <mutex>

/*
 * GLFWSession
 * adapted from "HelloWorld" example at <https://www.lwjgl.org/guide>
 */
class GLFWSession {
    private:
        std::recursive_mutex mtx{};
    public:
        Window* window{};
        Font* font{};
        long fps{};
    private:
        Screen* screen;
    public:
        // oops that signature ports a bit weirdly, whatever
        GLFWSession(const std::function<Screen*(GLFWSession*)>& initialScreen) : screen(initialScreen(this)) {
            init();
        };

        ~GLFWSession() {
            delete screen;
            delete window;
            delete font;
        }

    private:
        void init();
    public:
        void runLoop();

        void setScreen(Screen* screen) {
            mtx.lock();
            Screen* old = this->screen;
            this->screen = screen;
            delete old;
            screen->onWindowResize(window);
            mtx.unlock();
        }

    private:
        void loop();
    public:
        void onWindowResize(Window* window) {
            mtx.lock();
            screen->onWindowResize(window);
            mtx.unlock();
        }

        void onKey(int key, int scancode, int action, int mods) {
            screen->onKey(key, scancode, action, mods);
        }

        void onChar(unsigned int codepoint) {
            screen->onChar(codepoint);
        }

        void onMouseButton(int button, int action, int mods) {
            double cursorX, cursorY;
            glfwGetCursorPos(window->handle, &cursorX, &cursorY);
            screen->onMouseButton((float) cursorX, (float) cursorY, button, action, mods);
        }

        void onMousePos(double x, double y) {
            for (int i = 0; i < 6; ++i) {
                if (glfwGetMouseButton(window->handle, i) == GLFW_PRESS) {
                    screen->onMousePos((float) x, (float) y, i);
                }
            }
        }

        void onScroll(double xOffset, double yOffset) {
            double cursorX, cursorY;
            glfwGetCursorPos(window->handle, &cursorX, &cursorY);
            screen->onScroll((float) cursorX, (float) cursorY, (float) xOffset, (float) yOffset);
        }
};

#endif //BATTLESHIP_GLFWSESSION_H
