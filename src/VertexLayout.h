#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VertexLayout {

private:
    unsigned int index;
    int size;
    GLenum type;
    unsigned int stride;
    GLboolean normalized;
    void* offset;

public:
    VertexLayout(const unsigned int index, const int size, const GLenum type, const GLboolean normalized, const GLsizei stride, void* offset);

    unsigned int getIndex();
    int getSize();

    GLenum getType();
    unsigned int getStride();

    GLboolean isNormalized();

    void* getOffset();

};

