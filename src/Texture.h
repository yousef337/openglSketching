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

    Texture(const unsigned int offset);
    unsigned int getOffset() const;
    unsigned int getTexturId() const;
    std::string getType() const;
    virtual ~Texture() {};

};

