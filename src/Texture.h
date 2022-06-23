#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Intermediate/Image.h"

class Texture {

private:
    unsigned int textureId;
    unsigned int offset;
    std::string type;

public:

    virtual unsigned int getOffset() const {};

    virtual unsigned int getTexturId() const {};
    virtual ~Texture() {};

};

