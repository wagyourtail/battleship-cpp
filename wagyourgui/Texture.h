//
// Created by william on 3/10/22.
//

#ifndef BATTLESHIP_TEXTURE_H
#define BATTLESHIP_TEXTURE_H

#include <iostream>
#include <vector>
#include "GLFW/glfw3.h"
#include "../stb/stb_image.h"
#include "../stb/stb_image_resize.h"

class Texture {
    private:
        stbi_uc *data;
        int w, h, comp;
        GLuint texid{};
    public:
        Texture(const std::string &path);
        ~Texture() {
            glDeleteTextures(1, &texid);
            free(data);
        }

    private:
        void premultiplyAlpha();
        void upload();

    public:
        void bind();


};


#endif //BATTLESHIP_TEXTURE_H
