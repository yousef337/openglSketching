#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Intermediate/Image.h"
#include "Texture.h"

class ImagedTexture : public Texture {

private:
    Image imgTexture;

    void setUpTexture();
    void updateImage();

public:
    ImagedTexture();
    ImagedTexture(const Image img, const unsigned int offset = 0);
};

