#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "VAO.h"

    VAO::VAO(){
        glGenVertexArrays(1, &vaoId);
    }

    void VAO::setIndexCount(unsigned int count){
        indexCount = count;
    }

    unsigned int VAO::getVaoId(){
        return vaoId;
    }

    unsigned int VAO::getIndexCount(){
        return indexCount;
    }
