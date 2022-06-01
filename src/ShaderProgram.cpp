#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.cpp"

class ShaderProgram {

private:
    unsigned int programId;

public:

    ShaderProgram(){
        programId = glCreateProgram();
    }

    unsigned int getProgramId(){
        return programId;
    }

    void addShader(Shader shader){
        glAttachShader(programId, shader.getShaderId());
    }

    void linkProgram(){
        glLinkProgram(programId);
    }

};
