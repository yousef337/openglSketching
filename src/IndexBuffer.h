#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class IndexBuffer {

private:
    unsigned int indexedBufferId;

public:
    IndexBuffer();
    IndexBuffer(const void* indexedPositions, unsigned int size, GLenum usage);

    IndexBuffer(const void* indexedPositions, unsigned int size, GLenum usage, unsigned int vaoId);


    void setData(const void* indexedPositions, unsigned int size, GLenum usage);

    void bindToVAO(unsigned int vaoId);
    unsigned int getIndexBufferId();

};



