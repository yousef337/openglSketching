#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "VertexLayout.h"

class VBO {

private:
    unsigned int vboId;

public:
    VBO();
    void setData(const void* elements, unsigned int size, GLenum usage);

    void attributePointer(VertexLayout vertexLayout);

    unsigned int getVboId();
};


