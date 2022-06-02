#include <GL/glew.h>
#include <GLFW/glfw3.h>
#pragma once

class VAO {

private:
    unsigned int vaoId;
    unsigned int indexCount;

public:
    VAO(){
        glGenVertexArrays(1, &vaoId);
    }

    void setIndexCount(unsigned int count){
        indexCount = count;
    }

    unsigned int getVaoId(){
        return vaoId;
    }

    unsigned int getIndexCount(){
        return indexCount;
    }


};
