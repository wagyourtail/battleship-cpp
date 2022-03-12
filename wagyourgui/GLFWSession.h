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

class GLFWSession {
    public:
        Window *window{};
        Font *font{};
        long fps{};
    private:
        Screen *screen;
    public:
        // oops that signature ports a bit weirdly, whatever
        GLFWSession(Screen* (*func)(GLFWSession*)) : screen(func(this)) {
            init();
        };
        ~GLFWSession() {
            delete window;
            window = nullptr;
            delete font;
            font = nullptr;
        }
    private:
        void init();
    public:
        void runLoop();
        void setScreen(Screen *screen) {
            Screen *old = this->screen;
            this->screen = screen;
            if (old != nullptr) {
                delete old;
            }
            screen->onWindowResize(window);
        }
    private:
        void loop();
    public:
        void onWindowResize(Window *window) {
            screen->onWindowResize(window);
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
        void onScroll(double xoffset, double yoffset) {
            double cursorX, cursorY;
            glfwGetCursorPos(window->handle, &cursorX, &cursorY);
            screen->onScroll((float) cursorX, (float) cursorY, (float) xoffset, (float) yoffset);
        }
};

#endif //BATTLESHIP_GLFWSESSION_H
