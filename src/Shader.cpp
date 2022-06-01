#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Shader {

private:
    unsigned int shaderId;

    void errorHandling(const std::string shaderIdentifier){

    int results;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &results);

    if (results != GL_TRUE){

        int log_length = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &log_length);

        char* message = (char*) alloca(log_length * sizeof(char));

        glGetShaderInfoLog(shaderId, log_length, &log_length, message);

        std::cout << shaderIdentifier << std::endl;

        std::cout << message << std::endl;
    }
}


public:

    Shader(GLenum shaderType){
        shaderId = glCreateShader(shaderType);
    }


    Shader(GLenum shaderType, const std::string& shaderSource){
        shaderId = glCreateShader(shaderType);
        setResource(shaderSource);
    }

    unsigned int setResource(const std::string& shaderSource){

        const char* i = shaderSource.c_str();
            glShaderSource(shaderId, 1, &i, nullptr);
            glCompileShader(shaderId);

            errorHandling("Shader Id: " + std::to_string(shaderId));

            return shaderId;
        }

    void checkError(const std::string shaderIdentifier){
        errorHandling(shaderIdentifier);
    }

    unsigned int getShaderId(){
        return shaderId;
    }

};
