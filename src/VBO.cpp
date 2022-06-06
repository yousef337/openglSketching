#include "VBO.h"

    VBO::VBO(){
        glGenBuffers(1, &vboId);
    }

    void VBO::setData(const void* elements, unsigned int size, GLenum usage){
        glBindBuffer(GL_ARRAY_BUFFER, vboId);
        glBufferData(GL_ARRAY_BUFFER, size, elements, usage);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VBO::attributePointer(VertexLayout vertexLayout){
        glBindBuffer(GL_ARRAY_BUFFER, vboId);

        glVertexAttribPointer(vertexLayout.getIndex(), vertexLayout.getSize(), vertexLayout.getType(), vertexLayout.isNormalized(), vertexLayout.getStride(), vertexLayout.getOffset());
        glEnableVertexAttribArray(vertexLayout.getIndex());

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    unsigned int VBO::getVboId(){
        return vboId;
    }

