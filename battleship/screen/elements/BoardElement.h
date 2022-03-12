//
// Created by william on 3/11/22.
//

#ifndef BATTLESHIP_BOARDELEMENT_H
#define BATTLESHIP_BOARDELEMENT_H


#include "wagyourgui/elements/BaseElement.h"
#include "wagyourgui/elements/DisableableElement.h"
#include "wagyourgui/Font.h"
#include "battleship/BSPlayerGui.h"
#include <functional>
#include <utility>

class BoardElement : public BaseElement, public DisableableElement {
    protected:
        float x;
        float y;
        float width;
        Font *font;
        BSPlayerGui *player;
        std::function<void(BoardElement*, int, int)> onClickFn;
        bool disabled{false};
        bool renderHitBoard{};
    public:
        BoardElement(float x, float y, float width, Font *font, BSPlayerGui *player, std::function<void(BoardElement*, int, int)> onClick) : BaseElement(), x(x), y(y), width(width), font(font), player(player), onClickFn(std::move(onClick)) {}
        void setOnClick(std::function<void(BoardElement*, int, int)> onClick) {
            onClickFn = std::move(onClick);
        }
        void setDisabled(bool disabled) override { this->disabled = disabled; }
        bool isDisabled() override { return disabled; }
        virtual bool onClick(float x, float y, int button) override {
            if (!disabled) {
                int row = (y - this->y) / (width / 11);
                int col = (x - this->x) / (width / 11);
                if (row >= 1 && row < 11 && col >= 1 && col < 11) {
                    onClickFn(this, row - 1, col - 1);
                }
            }
            return true;
        }
        bool shouldFocus(float mouseX, float mouseY) override {
            return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + width;
        }
        virtual void onRender(float mouseX, float mouseY) override;
        virtual void renderHighlightCell(int row, int col);
};


#endif //BATTLESHIP_BOARDELEMENT_H
