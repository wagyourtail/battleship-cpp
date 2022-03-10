//
// Created by william on 3/9/22.
//

#ifndef BATTLESHIP_BASEELEMENT_H
#define BATTLESHIP_BASEELEMENT_H

class BaseElement {
    public:
        virtual bool onClick(float x, float y, int button) {return false;};
        virtual bool onScroll(float x, float y, float dx, float dy) {return false;};
        virtual bool onDrag(float x, float y, float dx, float dy, int button) {return false;};
        virtual bool onChar(unsigned int codepoint) {return false;};
        virtual bool onRelease(float x, float y, int button) {return false;};
        virtual bool onKey(int key, int scancode, int action, int mods) {return false;};
        virtual bool shouldFocus(float mouseX, float mouseY) {return false;};
        virtual void onFocus() {};
        virtual void onFocusLost() {};
        virtual void onRender(float mouseX, float mouseY) = 0;

};

#endif //BATTLESHIP_BASEELEMENT_H
