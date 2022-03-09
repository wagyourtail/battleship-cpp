//
// Created by william on 3/8/22.
//

#ifndef BATTLESHIP_WAGYOURGUI_H
#define BATTLESHIP_WAGYOURGUI_H

#include <unordered_set>
#include "../glfw/include/GLFW/glfw3.h"

class Screen {};

// declaration so window can see it...
class GLFWSession;

class Window {
    public:
        GLFWwindow *handle;
    private:
        bool visible{false};
        int width;
        int height;

    private:
        GLFWSession *parent;

    public:
        Window(const std::string& title, int width, int height, GLFWSession *parent);
};

class Font {};

class GLFWSession {
    public:
        Window *window{};
        Font *font{};
        long fps{};
    private:
        Screen *screen;
    public:
        // oops that signature ports a bit weirdly, whatever
        GLFWSession(Screen *(*func)(GLFWSession)) : screen(func(*this)) {
            init();
        };
    private:
        void init();
    public:
        void runLoop();
        void setScreen(Screen *screen);
    private:
        void loop();
    public:
        void onWindowResize(Window *window);
        void onKey(int key, int scancode, int action, int mods);
        void onChar(unsigned int codepoint);
        void onMouseButton(int button, int action, int mods);
        void onScroll(double xoffset, double yoffset);
};

#endif //BATTLESHIP_WAGYOURGUI_H
