//
// Created by william on 3/9/22.
//

#ifndef BATTLESHIP_GLBUILDER_H
#define BATTLESHIP_GLBUILDER_H

#include "GLFW/glfw3.h"
#include <iostream>
#include <cstdint>
#include <vector>


class GLBuilder {

    public:

        enum VertexFormat {
            POS_COL,
            POS_COL_TEX,
            POS_TEX
        };

    protected:

        struct Pos {
            float x, y;
        };

        struct Col {
            float r, g, b, a;
        };

        struct Tex {
            float u, v;
        };

    public:
        static GLBuilder& getImmediate();

    protected:
        static bool state;

    public:
        virtual GLBuilder& begin(GLenum mode, VertexFormat format) = 0;

        GLBuilder& begin(GLenum mode) {
            return begin(mode, POS_COL);
        }

        virtual GLBuilder& vertex(float x, float y) = 0;
        virtual GLBuilder& color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
        virtual GLBuilder& color(float r, float g, float b, float a) = 0;
        virtual GLBuilder& color(uint32_t rgb, float a) = 0;
        virtual GLBuilder& color(uint32_t rgba) = 0;
        virtual GLBuilder& uv(float u, float v) = 0;
        virtual GLBuilder& uv(float u, float v, float w, float h) = 0;
        virtual GLBuilder& next() = 0;
        virtual void end() = 0;

    private:
        class ImmediateBuilder;
};

class GLBuilder::ImmediateBuilder : public GLBuilder {

    private:
        VertexFormat format;
        Pos* pos{};
        Col* col{};
        Tex* tex{};

    protected:
        ImmediateBuilder() : format(POS_COL) {}

    public:
        static ImmediateBuilder& getInstance() {
            static ImmediateBuilder instance;
            return instance;
        }

    public:
        GLBuilder& begin(GLenum mode, VertexFormat format) override {
            if (state) throw std::runtime_error("already building");
            if (format == POS_COL) {
                glEnable(GL_COLOR);
                glDisable(GL_TEXTURE_2D);
            } else if (format == POS_COL_TEX) {
                glEnable(GL_COLOR);
                glEnable(GL_TEXTURE_2D);
            } else if (format == POS_TEX) {
                glDisable(GL_COLOR);
                glColor4f(1, 1, 1, 1);
                glEnable(GL_TEXTURE_2D);
            }
            glBegin(mode);
            this->format = format;
            state = true;
            return *this;
        }

        GLBuilder& vertex(float x, float y) override {
            if (!state) throw std::runtime_error("not building");
            if (pos != nullptr) throw std::runtime_error("already have pos");
            pos = new Pos{x, y};
            return *this;
        }

        GLBuilder& color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) override {
            if (!state) {
                glColor4f(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
                return *this;
            }
            if (format != POS_TEX) {
                if (col != nullptr) throw std::runtime_error("color already set");
                col = new Col{r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f};
            } else {
                throw std::runtime_error("current doesn't support color");
            }
            return *this;
        }

        GLBuilder& color(float r, float g, float b, float a) override {
            if (!state) {
                glColor4f(r, g, b, a);
                return *this;
            }
            if (format != POS_TEX) {
                if (col != nullptr) throw std::runtime_error("color already set");
                col = new Col{r, g, b, a};
            } else {
                throw std::runtime_error("current doesn't support color");
            }
            return *this;
        }

        GLBuilder& color(uint32_t rgb, float a) override {
            uint8_t r = (rgb >> 16) & 0xFF;
            uint8_t g = (rgb >> 8) & 0xFF;
            uint8_t b = rgb & 0xFF;
            return color(r, g, b, (uint8_t) a * 255);
        }

        GLBuilder& color(uint32_t argb) override {
            uint8_t a = (argb >> 24) & 0xFF;
            uint8_t r = (argb >> 16) & 0xFF;
            uint8_t g = (argb >> 8) & 0xFF;
            uint8_t b = argb & 0xFF;
            return color(r, g, b, a);
        }

        GLBuilder& uv(float u, float v) override {
            if (!state) throw std::runtime_error("not building");
            if (tex != nullptr) throw std::runtime_error("already have tex");
            tex = new Tex{u, v};
            return *this;
        }

        GLBuilder& uv(float u, float v, float w, float h) override {
            if (!state) throw std::runtime_error("not building");
            if (tex != nullptr) throw std::runtime_error("already have tex");
            tex = new Tex{u / w, v / h};
            return *this;
        }

        GLBuilder& next() override {
            if (!state) throw std::runtime_error("not building");
            if (pos == nullptr) throw std::runtime_error("no pos");
            if (format == POS_COL) {
                if (col != nullptr) glColor4f(col->r, col->g, col->b, col->a);
                glVertex2f(pos->x, pos->y);
            } else if (format == POS_COL_TEX) {
                if (col != nullptr) glColor4f(col->r, col->g, col->b, col->a);
                glTexCoord2f(tex->u, tex->v);
                glVertex2f(pos->x, pos->y);
            } else if (format == POS_TEX) {
                glTexCoord2f(tex->u, tex->v);
                glVertex2f(pos->x, pos->y);
            }
            delete pos;
            delete col;
            delete tex;
            pos = nullptr;
            col = nullptr;
            tex = nullptr;
            return *this;
        }

        void end() override {
            if (!state) throw std::runtime_error("not building");
            if (pos != nullptr || col != nullptr || tex != nullptr) {
                next();
            }
            glEnd();
            state = false;
        }

};

// todo: if i have time, implement the non-immediate pipeline here
// https://cpp.hotexamples.com/examples/-/-/glBufferData/cpp-glbufferdata-function-examples.html


#endif //BATTLESHIP_GLBUILDER_H
