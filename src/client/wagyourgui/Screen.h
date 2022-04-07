//
// Created by william on 3/9/22.
//

#ifndef BATTLESHIP_SCREEN_H
#define BATTLESHIP_SCREEN_H

#include <vector>
#include <memory>
#include "client/wagyourgui/elements/BaseElement.h"

class Window;

class GLFWSession;

class Screen {
    public:
        GLFWSession* parent;
        std::vector<std::shared_ptr<BaseElement>> elements{};
        std::shared_ptr<BaseElement> focused{};
        int width{};
        int height{};

        explicit Screen(GLFWSession* parent) : parent(parent) {};

        virtual ~Screen() {
            elements.clear();
        }

        void onWindowResize(Window* window);

    private:
        static float* sX;
        static float* sY;

    public:
        virtual void onMouseButton(float x, float y, int button, int action, int mods);
        virtual void onMousePos(float x, float y, int button);
        virtual bool onClick(float x, float y, int button);
        virtual bool onScroll(float x, float y, float dx, float dy);
        virtual bool onDrag(float x, float y, float dx, float dy, int button);
        virtual bool onChar(unsigned int codepoint);
        virtual bool onRelease(float x, float y, int button);
        virtual bool onKey(int key, int scancode, int action, int mods);
        virtual void onRender(float mouseX, float mouseY);

        virtual void init(Window* window) = 0;

    protected:
        template<typename T, typename std::enable_if<std::is_base_of<BaseElement, T>::value>::type* = nullptr>
        std::shared_ptr<T> addElement(const std::shared_ptr<T>& element) {
            elements.push_back(element);
            return element;
        }
};


#endif //BATTLESHIP_SCREEN_H
