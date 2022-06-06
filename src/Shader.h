#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Shader {

private:
    unsigned int shaderId;

    void errorHandling(const std::string shaderIdentifier);


public:

    Shader(GLenum shaderType);

    Shader(GLenum shaderType, const std::string& shaderSource);

    unsigned int setResource(const std::string& shaderSource);
    void checkError(const std::string shaderIdentifier);

    unsigned int getShaderId() const;
};

