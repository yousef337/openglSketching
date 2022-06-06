#include "IndexBuffer.h"

    IndexBuffer::IndexBuffer(){
        glGenBuffers(1, &indexedBufferId);
    }

    IndexBuffer::IndexBuffer(const void* indexedPositions, unsigned int size, GLenum usage){
        glGenBuffers(1, &indexedBufferId);
        setData(indexedPositions, size, usage);
    }

    IndexBuffer::IndexBuffer(const void* indexedPositions, unsigned int size, GLenum usage, unsigned int vaoId){
        glGenBuffers(1, &indexedBufferId);
        setData(indexedPositions, size, usage);
        bindToVAO(vaoId);
    }


    void IndexBuffer::setData(const void* indexedPositions, unsigned int size, GLenum usage){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexedBufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indexedPositions, usage);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::bindToVAO(unsigned int vaoId){
        glVertexArrayElementBuffer(vaoId, indexedBufferId);
    }

    unsigned int IndexBuffer::getIndexBufferId(){
        return indexedBufferId;
    }



