//
// Created by william on 3/9/22.
//

#define STB_TRUETYPE_IMPLEMENTATION
#include "Window.h"
#include "Font.h"

Font::Font(const std::string &path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open font file");
    }
    file.seekg(0, std::ios::end);
    int size = file.tellg();
    fontData.resize(size);
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char *>(&fontData[0]), size);
    file.close();
    if (!stbtt_InitFont(&fontInfo, &fontData[0], 0)) {
        throw std::runtime_error("Failed to load font");
    }

    stbtt_GetFontVMetrics(&fontInfo, &ascent, &descent, &lineGap);
    scale = stbtt_ScaleForPixelHeight(&fontInfo, (float) FONT_HEIGHT);
}

std::vector<stbtt_bakedchar> Font::init(int BITMAP_W, int BITMAP_H) {
    glGenTextures(1, &texid);
    std::vector<stbtt_bakedchar> cdata;
    cdata.resize(96);
    std::vector<unsigned char> bitmap;
    bitmap.resize(BITMAP_W * BITMAP_H);
    stbtt_BakeFontBitmap(fontData.data(), 0, 32,
                         bitmap.data(), BITMAP_W, BITMAP_H, 32, 96,
                         cdata.data());
    glBindTexture(GL_TEXTURE_2D, texid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, BITMAP_W, BITMAP_H, 0, GL_ALPHA, GL_UNSIGNED_BYTE,bitmap.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glClearColor(43.0f / 255, 43.0f / 255, 43.0f / 255, 0);
    glColor3f(169.f / 255, 183.f / 255, 198.f / 255);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return cdata;
}

float Font::drawString(const std::string &text, float x, float y) {
    // move to top instead of bottom
    y += FONT_HEIGHT;

    if (cdata.empty()) {
        cdata = init(1024, 1024);
    }
    glBindTexture(GL_TEXTURE_2D, texid);

    stbtt_aligned_quad q;
    float xP = 0, yP = 0;

    int pCodepoint;
    int lineStart = 0;
    float lineY = 0;

    float x1 = 0;

    glBegin(GL_QUADS);
    for (int i = 0, to = text.length(); i < to;) {
        i += getCP(text, to, i, &pCodepoint);
        int cp = pCodepoint;
        if (cp == '\n') {
            throw std::runtime_error("Newline not supported");
        }
        float cpX = xP;
        float cpY = yP;
        stbtt_GetBakedQuad(cdata.data(), 1024, 1024, cp - 32, &xP, &yP, &q, 1);
        xP = scaler(cpX, xP, 1);
        //kerning
        if (i < to) {
            getCP(text, to, i, &pCodepoint);
            xP = xP + (float) stbtt_GetCodepointKernAdvance(&fontInfo, cp, pCodepoint - 32);
        }
        float x0 = scaler(cpX, q.x0, 1);
        float y0 = scaler(cpY, q.y0, 1);
        x1 = scaler(cpX, q.x1, 1);
        float y1 = scaler(cpY, q.y1, 1);

        glTexCoord2f(q.s0, q.t0);
        glVertex2f(x0 + x, y0 + y);

        glTexCoord2f(q.s1, q.t0);
        glVertex2f(x1 + x, y0 + y);

        glTexCoord2f(q.s1, q.t1);
        glVertex2f(x1 + x, y1 + y);

        glTexCoord2f(q.s0, q.t1);
        glVertex2f(x0 + x, y1 + y);
    }
    glEnd();

    return x1;
}

float Font::getWidth(const std::string &text) {
    int width = 0;
    int pCodepoint;
    int pAdvancedWidth;
    int pLeftSizeBearing;

    int i = 0;
    while (i < text.length()) {
        i += getCP(text, text.length(), i, &pCodepoint);
        int cp = pCodepoint;

        stbtt_GetCodepointHMetrics(&fontInfo, pCodepoint, &pAdvancedWidth, &pLeftSizeBearing);
        width += pAdvancedWidth;

        // kerning
        if (i < text.length()) {
            getCP(text, text.length(), i, &pCodepoint);
            width += stbtt_GetCodepointKernAdvance(&fontInfo, cp, pCodepoint);
        }
    }

    return width * scale * 2;
    // idk why *2, but it works
}

float Font::drawTrimmedString(const std::string &text, float x, float y, float width) {
    // move to top instead of bottom
    y += FONT_HEIGHT;

    if (cdata.empty()) {
        cdata = init(1024, 1024);
    }
    glBindTexture(GL_TEXTURE_2D, texid);

    stbtt_aligned_quad q;
    float xP, yP;

    int pCodepoint;
    int lineStart = 0;
    float lineY = 0;

    glBegin(GL_QUADS);
    float x1;
    for (int i = 0, to = text.length(); i < to;) {
        i += getCP(text, to, i, &pCodepoint);
        int cp = pCodepoint;
        if (cp == '\n') {
            throw std::runtime_error("Newline not supported");
        }
        float cpX = xP;
        float cpY = yP;
        stbtt_GetBakedQuad(cdata.data(), 1024, 1024, cp - 32, &xP, &yP, &q, 1);
        xP = scaler(cpX, xP, 1);
        //kerning
        if (i < to) {
            getCP(text, to, i, &pCodepoint);
            xP = xP + (float) stbtt_GetCodepointKernAdvance(&fontInfo, cp, pCodepoint - 32);
        }
        float x0 = scaler(cpX, q.x0, 1);
        float y0 = scaler(cpY, q.y0, 1);
        x1 = scaler(cpX, q.x1, 1);
        float y1 = scaler(cpY, q.y1, 1);

        if (x1 - x > width) {
            glEnd();
            return x0;
        }

        glTexCoord2f(q.s0, q.t0);
        glVertex2f(x0 + x, y0 + y);

        glTexCoord2f(q.s1, q.t0);
        glVertex2f(x1 + x, y0 + y);

        glTexCoord2f(q.s1, q.t1);
        glVertex2f(x1 + x, y1 + y);

        glTexCoord2f(q.s0, q.t1);
        glVertex2f(x0 + x, y1 + y);
    }
    glEnd();

    return x1;
}

int Font::getCP(const std::string &text, int to, int i, int *cpOut) {
    int c1 = text[i];
    // skipping high surrogate support
    *cpOut = c1;
    return 1;
}