#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class IndexBuffer {

private:
    unsigned int indexedBufferId;

public:
    IndexBuffer(){
        glGenBuffers(1, &indexedBufferId);
    }

    IndexBuffer(const void* indexedPositions, unsigned int size, GLenum usage){
        glGenBuffers(1, &indexedBufferId);
        setData(indexedPositions, size, usage);
    }

    IndexBuffer(const void* indexedPositions, unsigned int size, GLenum usage, unsigned int vaoId){
        glGenBuffers(1, &indexedBufferId);
        setData(indexedPositions, size, usage);
        bindToVAO(vaoId);
    }


    void setData(const void* indexedPositions, unsigned int size, GLenum usage){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexedBufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indexedPositions, usage);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void bindToVAO(unsigned int vaoId){
        glVertexArrayElementBuffer(vaoId, indexedBufferId);
    }

    unsigned int getIndexBufferId(){
        return indexedBufferId;
    }

};


