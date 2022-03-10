//
// Created by william on 3/9/22.
//

#ifndef BATTLESHIP_WINDOW_H
#define BATTLESHIP_WINDOW_H

#include "GLFW/glfw3.h"
#include <iostream>

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
        void setupFramebuffer();
        ~Window() {
            glfwDestroyWindow(handle);
        }
        int getWidth() const { return width; }
        int getHeight() const { return height; }
        void setVisible(bool visible) {
            if (visible) {
                glfwShowWindow(handle);
            } else {
                glfwHideWindow(handle);
            }
            this->visible = visible;
        }
        bool isVisible() const { return visible; }
};

#endif //BATTLESHIP_WINDOW_H
