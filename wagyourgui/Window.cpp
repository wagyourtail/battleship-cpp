//
// Created by william on 3/9/22.
//

#include "Window.h"
#include "GLFWSession.h"

Window::Window(const std::string &title, int width, int height, GLFWSession *parent) : handle(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr)), width(width), height(height), parent(parent) {
    if (handle == nullptr) {
        throw std::runtime_error("Failed to create window");
    }

    // allow reference to this from window...
    glfwSetWindowUserPointer(handle, this);

    glfwSetWindowSizeCallback(handle, [] (GLFWwindow *window, int width, int height) {
        auto* thisRef = (Window*) glfwGetWindowUserPointer(window);
        thisRef->width = width;
        thisRef->height = height;
        thisRef->parent->onWindowResize(thisRef);
    });

    glfwSetMouseButtonCallback(handle, [] (GLFWwindow *window, int button, int action, int mods) {
        auto* thisRef = (Window*) glfwGetWindowUserPointer(window);
        thisRef->parent->onMouseButton(button, action, mods);
    });

    glfwSetCharCallback(handle, [] (GLFWwindow *window, unsigned int codepoint) {
        auto* thisRef = (Window*) glfwGetWindowUserPointer(window);
        thisRef->parent->onChar(codepoint);
    });

    glfwSetKeyCallback(handle, [] (GLFWwindow *window, int key, int scancode, int action, int mods) {
        auto* thisRef = (Window*) glfwGetWindowUserPointer(window);
        thisRef->parent->onKey(key, scancode, action, mods);
    });

    glfwSetScrollCallback(handle, [] (GLFWwindow *window, double xOffset, double yOffset) {
        auto* thisRef = (Window*) glfwGetWindowUserPointer(window);
        thisRef->parent->onScroll(xOffset, yOffset);
    });
}

void Window::setupFramebuffer() {
    int width, height;
    glfwGetFramebufferSize(handle, &width, &height);
    this->width = width;
    this->height = height;
    glViewport(0, 0, width, height);

    parent->onWindowResize(this);
}