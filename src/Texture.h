#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Intermediate/Image.h"

class Texture{

private:
    unsigned int textureId;
    unsigned int offset;
    Image imgTexture;

    void setUpTexture();

    void updateImage();

public:
    Texture();
    Texture(const Image img, const unsigned int offset = 0);

    unsigned int getOffset() const;

    unsigned int getTexturId() const;

};

