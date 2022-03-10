//
// Created by william on 3/9/22.
//

#include "Screen.h"
#include "Window.h"
#include "elements/BaseElement.h"

void Screen::onWindowResize(Window *window) {
    width = window->getWidth();
    height = window->getHeight();
    elements.clear();
    focused = nullptr;
    init(window);
}

void Screen::onMouseButton(float x, float y, int button, int action, int mods) {
    switch (action) {
        case GLFW_PRESS:
            onClick(x, y, button);
            if (button < 6) {
                sX[button] = x;
                sY[button] = y;
            }
            break;
        case GLFW_RELEASE:
            onRelease(x, y, button);
            break;
        case GLFW_REPEAT:
            if (button < 6) {
                onDrag(x, y, x - sX[button], y - sY[button], button);
                sX[button] = x;
                sY[button] = y;
            }
            break;
    }
}

bool Screen::onClick(float x, float y, int button) {
    bool unfocus = true;
    for (auto &element : elements) {
        if (element->shouldFocus(x, y)) {
            BaseElement *old = focused;
            focused = element;
            if (old != nullptr) {
                old->onFocusLost();
            }
            element->onFocus();
            unfocus = false;
        }
    }
    if (unfocus) {
        if (focused != nullptr) {
            focused->onFocusLost();
        }
        focused = nullptr;
    }

    if (focused != nullptr) {
        return focused->onClick(x, y, button);
    }

    return false;
}

bool Screen::onScroll(float x, float y, float dx, float dy) {
    if (focused != nullptr) {
        return focused->onScroll(x, y, dx, dy);
    }
    return false;
}

bool Screen::onDrag(float x, float y, float dx, float dy, int button) {
    if (focused != nullptr) {
        return focused->onDrag(x, y, dx, dy, button);
    }
    return false;
}

bool Screen::onChar(unsigned int codepoint) {
    if (focused != nullptr) {
        return focused->onChar(codepoint);
    }
    return false;
}

bool Screen::onRelease(float x, float y, int button) {
    if (focused != nullptr) {
        return focused->onRelease(x, y, button);
    }
    return false;
}

bool Screen::onKey(int key, int scancode, int action, int mods) {
    if (focused != nullptr) {
        return focused->onKey(key, scancode, action, mods);
    }
    return false;
}

void Screen::onRender(float mouseX, float mouseY) {
    for (auto &element : elements) {
        element->onRender(mouseX, mouseY);
    }
}
