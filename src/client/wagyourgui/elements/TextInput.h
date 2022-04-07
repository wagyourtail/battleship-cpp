//
// Created by william on 4/6/22.
//

#ifndef BATTLESHIP_SERVER_TEXTINPUT_H
#define BATTLESHIP_SERVER_TEXTINPUT_H

#include "Button.h"
#include <regex>
#include <string>
#include <utility>

// adapted from myself @ https://github.com/wagyourtail/JsMacros/blob/main-1.18/common/src/main/java/xyz/wagyourtail/wagyourgui/elements/TextInput.java

class TextInput : public Button {
    public:
        std::function<void(std::string&)> onChange;
        std::basic_regex<char> regex{"^.*$"};
        std::string content;
    protected:
        uint32_t selColor;
        float selStart{};
    public:
        int selStartIndex{};
    protected:
        float selEnd{};
    public:
        int selEndIndex{};
    protected:
        int arrowCursor;

        float font_scale{.8};

        bool focused{false};
    public:
        TextInput(
                float x,
                float y,
                float width,
                float height,
                Font* textRenderer,
                uint32_t color,
                uint32_t borderColor,
                uint32_t hilightColor,
                uint32_t textColor,
                std::string message,
                std::function<void(Button*)> onClick,
                std::function<void(std::string&)> onChange
        ) :
                Button(
                        x,
                        y,
                        width,
                        height,
                        textRenderer,
                        "",
                        color,
                        borderColor,
                        textColor,
                        borderColor,
                        std::move(onClick)), selColor(hilightColor), content(std::move(message)),
                onChange(std::move(onChange)) {
            updateSelStart(content.length());
            updateSelEnd(content.length());
            arrowCursor = content.length();
        }

        void setMessage(std::string message) {
            content = std::move(message);
        }

        void updateSelStart(int startIndex) {
            selStartIndex = startIndex;
            if (startIndex == 0) { selStart = x + 1; }
            else { selStart = x + 2 + font->getWidth(content.substr(0, startIndex)) * font_scale; }
        }

        void updateSelEnd(int endIndex) {
            selEndIndex = endIndex;
            if (endIndex == 0) { selEnd = x + 2; }
            else { selEnd = x + 3 + font->getWidth(content.substr(0, endIndex)) * font_scale; }
        }

        bool onClick(float mouseX, float mouseY, int btn) override;
        bool onDrag(float x, float y, float dx, float dy, int button) override;

    protected:
        void swapStartEnd() {
            int temp1 = selStartIndex;
            updateSelStart(selEndIndex);
            updateSelEnd(temp1);
        }

    public:
        bool onKey(int key, int scancode, int action, int mods) override;
        bool onChar(unsigned int codepoint) override;

        void onFocus() override {
            focused = true;
        }

        void onFocusLost() override {
            focused = false;
        }

        void onRender(float mouseX, float mouseY) override;
};


#endif //BATTLESHIP_SERVER_TEXTINPUT_H
