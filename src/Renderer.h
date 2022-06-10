#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "VAO.h"

class Renderer{


public:

    void clear();

    void drawTrinanglerElement(VAO vao, unsigned int shaderProgramId, unsigned int texturId) const;
    void drawTrinanglerElement(VAO vao, unsigned int shaderProgramId) const;

};

