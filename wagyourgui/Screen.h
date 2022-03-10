//
// Created by william on 3/9/22.
//

#ifndef BATTLESHIP_SCREEN_H
#define BATTLESHIP_SCREEN_H

#include <vector>
#include "elements/BaseElement.h"

class Window;
class GLFWSession;

class Screen {
    public:
        GLFWSession *session;
        std::vector<BaseElement*> elements{};
        BaseElement *focused{};
        int width{};
        int height{};
        explicit Screen(GLFWSession *session) : session(session) {};
        void onWindowResize(Window *window);

    private:
        float *sX = new float[6];
        float *sY = new float[6];

    public:
        virtual void onMouseButton(float x, float y, int button, int action, int mods);
        virtual bool onClick(float x, float y, int button);
        virtual bool onScroll(float x, float y, float dx, float dy);
        virtual bool onDrag(float x, float y, float dx, float dy, int button);
        virtual bool onChar(unsigned int codepoint);
        virtual bool onRelease(float x, float y, int button);
        virtual bool onKey(int key, int scancode, int action, int mods);
        virtual void onRender(float mouseX, float mouseY);

        virtual void init(Window *window) = 0;
};

#include "Window.h"
#include "GLFWSession.h"

#endif //BATTLESHIP_SCREEN_H
