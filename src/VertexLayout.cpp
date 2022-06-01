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
    VertexLayout(const unsigned int index, const int size, const GLenum type, const GLboolean normalized, const GLsizei stride, void* offset){
        this->index = index;
        this->size = size;
        this->type = type;
        this->normalized = normalized;
        this->stride = stride;
        this->offset = offset;
    }

    unsigned int getIndex(){
     return index;
    }

    int getSize(){
        return size;
    }

    GLenum getType(){
        return type;
    }

    unsigned int getStride(){
        return stride;
    }

    GLboolean isNormalized(){
        return normalized;
    }

    void* getOffset(){
        return offset;
    }

};
