//
// Created by william on 3/9/22.
//

#ifndef BATTLESHIP_BUTTON_H
#define BATTLESHIP_BUTTON_H

#include <utility>
#include <functional>

#include "BaseElement.h"
#include "DisableableElement.h"
#include "client/wagyourgui/Font.h"

class Button : public BaseElement, public DisableableElement {
    protected:
        float x;
        float y;
        float width;
        float height;
        Font* font;
        std::string text;
        uint32_t color;
        uint32_t hoverColor;
        uint32_t textColor;
        uint32_t hoverTextColor;
        uint32_t borderColor;
        std::function<void(Button*)> onClickFn;
        bool active;
    public:
        Button(
                float x,
                float y,
                float width,
                float height,
                Font* font,
                std::string text,
                uint32_t color,
                uint32_t hoverColor,
                uint32_t textColor,
                uint32_t hoverTextColor,
                uint32_t borderColor,
                std::function<void(Button*)> onClick
        ) :
                BaseElement(), x(x), y(y), width(width), height(height), font(font), text(std::move(text)),
                color(color), hoverColor(hoverColor), textColor(textColor), hoverTextColor(hoverTextColor),
                borderColor(borderColor), onClickFn(std::move(onClick)), active(true) {}

        Button(
                float x,
                float y,
                float width,
                float height,
                Font* font,
                std::string text,
                uint32_t color,
                uint32_t hoverColor,
                uint32_t textColor,
                uint32_t borderColor,
                std::function<void(Button*)> onClick
        ) :
                BaseElement(), x(x), y(y), width(width), height(height), font(font), text(std::move(text)),
                color(color), hoverColor(hoverColor), textColor(textColor), hoverTextColor(textColor),
                borderColor(borderColor), onClickFn(onClick), active(true) {}

        void setOnClick(std::function<void(Button*)> onClick) { this->onClickFn = onClick; }

        void setPos(float x, float y, float width, float height) {
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
        }

        void setText(std::string text) { this->text = std::move(text); }

        void setColor(uint32_t color) { this->color = color; }

        void setHoverColor(uint32_t hoverColor) { this->hoverColor = hoverColor; }

        void setTextColor(uint32_t textColor) { this->textColor = textColor; }

        void setHoverTextColor(uint32_t hoverTextColor) { this->hoverTextColor = hoverTextColor; }

        void setBorderColor(uint32_t borderColor) { this->borderColor = borderColor; }

        float getX() { return x; }

        float getY() { return y; }

        float getWidth() { return width; }

        float getHeight() { return height; }

        std::string getText() { return text; }

        uint32_t getColor() { return color; }

        uint32_t getHoverColor() { return hoverColor; }

        uint32_t getTextColor() { return textColor; }

        uint32_t getHoverTextColor() { return hoverTextColor; }

        uint32_t getBorderColor() { return borderColor; }

        virtual bool shouldFocus(float mouseX, float mouseY) override {
            return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
        }

        virtual bool onClick(float mouseX, float mouseY, int btn) override {
            if (active) {
                onClickFn(this);
            }
            return true;
        }

        virtual void onRender(float mouseX, float mouseY);

        void setDisabled(bool disabled) override { this->active = !disabled; }

        bool isDisabled() override { return !active; }
};


#endif //BATTLESHIP_BUTTON_H
