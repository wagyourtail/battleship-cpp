//
// Created by william on 3/11/22.
//

#ifndef BATTLESHIP_BOARDELEMENT_H
#define BATTLESHIP_BOARDELEMENT_H


#include "src/wagyourgui/elements/BaseElement.h"
#include "src/wagyourgui/elements/DisableableElement.h"
#include "src/wagyourgui/Font.h"
#include "src/battleship/BSPlayerGui.h"
#include <functional>

class BoardElement : public BaseElement, public DisableableElement {
    protected:
        float x;
        float y;
        float width;
        Font *font;
        BSPlayerGui *player;
        std::function<void(BoardElement*, int, int, int)> onClickFn;
        bool disabled{false};
        bool renderHitBoard{};
        std::function<void(BoardElement*, int, int)> onRenderHighlightFn;
    public:
        BoardElement(float x, float y, float width, Font *font, BSPlayerGui *player, std::function<void(BoardElement*, int, int, int)> onClick, std::function<void(BoardElement*, int, int)> onRenderHighlightFn) : BaseElement(), x(x), y(y), width(width), font(font), player(player), onClickFn(std::move(onClick)), onRenderHighlightFn(std::move(onRenderHighlightFn)) {}
        void setOnClick(std::function<void(BoardElement*, int, int, int)> onClick) {
            onClickFn = std::move(onClick);
        }
        void setDisabled(bool disabled) override { this->disabled = disabled; }
        bool isDisabled() override { return disabled; }
        virtual bool onClick(float x, float y, int button) override {
            if (!disabled) {
                int row = (y - this->y) / (width / 11);
                int col = (x - this->x) / (width / 11);
                if (row >= 1 && row < 11 && col >= 1 && col < 11) {
                    onClickFn(this, row - 1, col - 1, button);
                }
            }
            return true;
        }
        bool shouldFocus(float mouseX, float mouseY) override {
            return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + width;
        }
        float getWidth() const { return width; }
        void setRenderHitBoard(bool renderHitBoard) { this->renderHitBoard = renderHitBoard; }
        void onRender(float mouseX, float mouseY) override;
};


#endif //BATTLESHIP_BOARDELEMENT_H
