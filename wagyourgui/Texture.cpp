//
// Created by william on 3/10/22.
//

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "Texture.h"
#include <fstream>

#define max(a, b) (((a) > (b)) ? (a) : (b))

Texture::Texture(const std::string &path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + path);
    }
    file.seekg(0, std::ios::end);
    std::vector<unsigned char> imageData{};
    int size = file.tellg();
    imageData.resize(size);
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char *>(&imageData[0]), size);
    file.close();

    stbi_set_flip_vertically_on_load(true);

    if (!stbi_info_from_memory(&imageData[0], size, &w, &h, &comp)) {
        throw std::runtime_error("Could not read image data from file: " + path);
    }

    std::cout << "Image size: " << w << "x" << h << std::endl;
    std::cout << "Image components: " << comp << std::endl;

    // decode image data
    data = stbi_load_from_memory(&imageData[0], size, &w, &h, &comp, 4);
    if (data == nullptr) {
        throw std::runtime_error("Could not decode image data from file: " + path);
    }
}

void Texture::upload() {
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texid);

    glBindTexture(GL_TEXTURE_2D, texid);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    int format;
    if (comp == 3) {
        if ((w & 3) != 0) {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 2 - (w & 1));
        }
        format = GL_RGB;
    } else {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        format = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, format, GL_UNSIGNED_BYTE, data);

}

void Texture::bind() {
    if (texid == 0) {
        upload();
    }
    glBindTexture(GL_TEXTURE_2D, texid);
}