//
// Created by william on 3/9/22.
//

#ifndef BATTLESHIP_FONT_H
#define BATTLESHIP_FONT_H

#include <fstream>
#include <vector>

#include "../stb/stb_truetype.h"

class Font {
    public:
        stbtt_fontinfo fontInfo{};
        std::vector<unsigned char> fontData{};
    private:
        float scale;
        int ascent{};
        int descent{};
        int lineGap{};
        std::vector<stbtt_bakedchar> cdata;
    public:
        const int FONT_HEIGHT = 16;
        Font(const std::string& path);
    private:
        std::vector<stbtt_bakedchar> init(int BITMAP_W, int BITMAP_H);

    public:
        float drawString(const std::string& text, float x, float y);
        float getWidth(const std::string& text);
        float drawTrimmedString(const std::string& text, float x, float y, float width);
    private:
        static int getCP(const std::string& text, int to, int i, int* cpOut);
        static float scaler(float center, float offset, float factor) {
            return (offset - center) * factor + center;
        }

};

#endif //BATTLESHIP_FONT_H
