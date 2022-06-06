#include "VertexLayout.h"

    VertexLayout::VertexLayout(const unsigned int index, const int size, const GLenum type, const GLboolean normalized, const GLsizei stride, void* offset){
        this->index = index;
        this->size = size;
        this->type = type;
        this->normalized = normalized;
        this->stride = stride;
        this->offset = offset;
    }

    unsigned int VertexLayout::getIndex(){
     return index;
    }

    int VertexLayout::getSize(){
        return size;
    }

    GLenum VertexLayout::getType(){
        return type;
    }

    unsigned int VertexLayout::getStride(){
        return stride;
    }

    GLboolean VertexLayout::isNormalized(){
        return normalized;
    }

    void* VertexLayout::getOffset(){
        return offset;
    }
