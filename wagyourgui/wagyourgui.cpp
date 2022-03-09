//
// Created by william on 3/8/22.
//

#include <stdexcept>
#include <iostream>
#include "wagyourgui.h"

void GLFWSession::runLoop() {
    loop();

    delete window;
    window = nullptr;
    delete font;
    font = nullptr;
    glfwTerminate();
    glfwSetErrorCallback(nullptr);
}

void errStream(int errCode, const char *errMsg) {
    std::cerr << "GLFW Error: " << errMsg << std::endl;
}

void GLFWSession::init() {
    glfwSetErrorCallback(errStream);

    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);



}

Window::Window(const std::string &title, int width, int height, GLFWSession *parent) : handle(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr)), width(width), height(height), parent(parent) {
    if (handle == nullptr) {
        throw std::runtime_error("Failed to create window");
    }

    // allow reference to this from window...
    glfwSetWindowUserPointer(handle, this);

    glfwSetWindowSizeCallback(handle, [] (GLFWwindow *window, int width, int height) {
        Window* thisRef = (Window*) glfwGetWindowUserPointer(window);
        thisRef->width = width;
        thisRef->height = height;
        thisRef->parent->onWindowResize(thisRef);
    });

    glfwSetMouseButtonCallback(handle, [] (GLFWwindow *window, int button, int action, int mods) {
        Window* thisRef = (Window*) glfwGetWindowUserPointer(window);
        thisRef->parent->onMouseButton(button, action, mods);
    });

    glfwSetCharCallback(handle, [] (GLFWwindow *window, unsigned int codepoint) {
        Window* thisRef = (Window*) glfwGetWindowUserPointer(window);
        thisRef->parent->onChar(codepoint);
    });

    glfwSetKeyCallback(handle, [] (GLFWwindow *window, int key, int scancode, int action, int mods) {
        Window* thisRef = (Window*) glfwGetWindowUserPointer(window);
        thisRef->parent->onKey(key, scancode, action, mods);
    });

    glfwSetScrollCallback(handle, [] (GLFWwindow *window, double xOffset, double yOffset) {
        Window* thisRef = (Window*) glfwGetWindowUserPointer(window);
        thisRef->parent->onScroll(xOffset, yOffset);
    });
}