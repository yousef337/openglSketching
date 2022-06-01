#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "VertexLayout.cpp"

class VBO {

private:
    unsigned int vboId;

public:
    VBO(){
        glGenBuffers(1, &vboId);
    }

    void setData(const void* elements, unsigned int size, GLenum usage){
        glBindBuffer(GL_ARRAY_BUFFER, vboId);
        glBufferData(GL_ARRAY_BUFFER, size, elements, usage);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void attributePointer(VertexLayout vertexLayout){
        glBindBuffer(GL_ARRAY_BUFFER, vboId);

        glVertexAttribPointer(vertexLayout.getIndex(), vertexLayout.getSize(), vertexLayout.getType(), vertexLayout.isNormalized(), vertexLayout.getStride(), vertexLayout.getOffset());
        glEnableVertexAttribArray(vertexLayout.getIndex());

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    unsigned int getVboId(){
        return vboId;
    }

};

