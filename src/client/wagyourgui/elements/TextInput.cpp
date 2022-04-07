//
// Created by william on 4/6/22.
//

#include "TextInput.h"
#include "client/wagyourgui/DrawableHelper.h"

template<class T, class U>
inline auto min(T a, U b) -> decltype(a + b) {
    return a < b ? a : b;
}

bool TextInput::onClick(float mouseX, float mouseY, int btn) {
    if (this->focused) {
        int pos = font->trimToWidth(this->content, mouseX - x - 2).length();
        updateSelStart(pos);
        updateSelEnd(pos);
        arrowCursor = pos;
    }
    return Button::onClick(mouseX, mouseY, btn);
}

bool TextInput::onDrag(float x, float y, float dx, float dy, int button) {
    if (this->focused) {
        int pos = font->trimToWidth(this->content, x - this->x - 2).length();
        updateSelEnd(pos);
        arrowCursor = pos;
    }
    return true;
}

bool TextInput::onKey(int key, int scancode, int action, int mods) {
    bool ctrl_pressed = (mods & GLFW_MOD_CONTROL) != 0;
    if (this->focused && action == GLFW_PRESS) {
        if (selEndIndex < selStartIndex) swapStartEnd();
        if (ctrl_pressed && key == GLFW_KEY_A) {
            this->updateSelStart(0);
            this->updateSelEnd(this->content.length());
        } else if (ctrl_pressed && key == GLFW_KEY_C) {
            // unimplemented, too hard for time left
            // https://stackoverflow.com/questions/6436257/how-do-you-copy-paste-from-the-clipboard-in-c
        } else if (ctrl_pressed && key == GLFW_KEY_X) {
            // unimplemented, too hard for time left
            // https://stackoverflow.com/questions/6436257/how-do-you-copy-paste-from-the-clipboard-in-c
        } else if (ctrl_pressed && key == GLFW_KEY_V) {
            // unimplemented, too hard for time left
            // https://stackoverflow.com/questions/6436257/how-do-you-copy-paste-from-the-clipboard-in-c
        }
        switch (key) {
            case GLFW_KEY_BACKSPACE:
                if (selStartIndex == selEndIndex && selStartIndex > 0) updateSelStart(selStartIndex - 1);
                content = content.substr(0, selStartIndex) + (selEndIndex >= content.length() ? "" : content.substr(selEndIndex));
                onChange(content);
                updateSelEnd(selStartIndex);
                arrowCursor = selStartIndex;
                break;
            case GLFW_KEY_DELETE:
                if (selStartIndex == selEndIndex && selEndIndex < content.length()) updateSelEnd(selEndIndex + 1);
                content = content.substr(0, selStartIndex) + content.substr(selEndIndex);
                onChange(content);
                updateSelEnd(selStartIndex);
                arrowCursor = selStartIndex;
                break;
            case GLFW_KEY_HOME:
                updateSelStart(0);
                updateSelEnd(selStartIndex);
                arrowCursor = selStartIndex;
                break;
            case GLFW_KEY_END:
                updateSelStart(content.length());
                updateSelEnd(selStartIndex);
                arrowCursor = selStartIndex;
                break;
            case GLFW_KEY_LEFT:
                if (arrowCursor > 0) {
                    if (arrowCursor < selEndIndex) {
                        updateSelStart(--arrowCursor);
                        if (!ctrl_pressed) updateSelEnd(selStartIndex);
                    } else if (arrowCursor >= selEndIndex) {
                        updateSelEnd(--arrowCursor);
                        if (!ctrl_pressed) updateSelStart(selEndIndex);
                    }
                }
                break;
            case GLFW_KEY_RIGHT:
                if (arrowCursor < content.length()) {
                    if (arrowCursor < selEndIndex) {
                        updateSelStart(++arrowCursor);
                        if (!ctrl_pressed) updateSelEnd(selStartIndex);
                    } else {
                        updateSelEnd(++arrowCursor);
                        if (!ctrl_pressed) updateSelStart(selEndIndex);
                    }
                }
            default:
                break;
        }
    }
    return true;
}

bool TextInput::onChar(unsigned int codepoint) {
    if (selEndIndex < selStartIndex) swapStartEnd();
    std::string newContent;
    if (selEndIndex >= content.length())
        newContent = content.substr(0, selStartIndex) + (char)codepoint;
    else
        newContent = content.substr(0, selStartIndex) + (char)codepoint + content.substr(selEndIndex);
    if (std::regex_match(newContent, regex)) {
        content = std::move(newContent);
        onChange(content);
        updateSelStart(selStartIndex + 1);
        arrowCursor = selStartIndex;
        updateSelEnd(arrowCursor);
    }
    return true;
}

using namespace DrawableHelper;

void TextInput::onRender(float mouseX, float mouseY) {
    bool hover = mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;

    // Draw background
    rect(x, y, x + width, y + height, hover ? hoverColor : color);

    // Draw border
    rect(x, y, x + 1, y + height, borderColor);
    rect(x + width - 1, y, x + width, y + height, borderColor);
    rect(x + 1, y, x + width - 1, y + 1, borderColor);
    rect(x + 1, y + height - 1, x + width - 1, y + height, borderColor);

    // Draw text
    float scaled_font_height = font->FONT_HEIGHT * font_scale;
    rect(selStart, height > scaled_font_height ? y + 2 : y, min(selEnd, x + width - 2), (height > scaled_font_height ? y + 2 : y) + scaled_font_height + 4, selColor);
    // push a matrix
    glPushMatrix();
    // translate to the right spot and scale
    glTranslatef(x + 4, y + (height > scaled_font_height ? 2 : 0), 0);
    glScalef(font_scale, font_scale, 1);
    // draw the text
    drawTrimmedString(font, content, 0, 0, (width - 4) / font_scale, textColor);
    // pop the matrix
    glPopMatrix();
}

