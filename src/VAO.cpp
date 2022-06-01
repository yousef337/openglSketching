#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VAO {

private:
    unsigned int vaoId;

public:
    VAO(){
        glGenVertexArrays(1, &vaoId);
    }

    unsigned int getVaoId(){
        return vaoId;
    }

};
