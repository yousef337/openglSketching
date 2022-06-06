#include "Shader.h"

    void Shader::errorHandling(const std::string shaderIdentifier){

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

    Shader::Shader(GLenum shaderType){
        shaderId = glCreateShader(shaderType);
    }


    Shader::Shader(GLenum shaderType, const std::string& shaderSource){
        shaderId = glCreateShader(shaderType);
        setResource(shaderSource);
    }

    unsigned int Shader::setResource(const std::string& shaderSource){

        const char* i = shaderSource.c_str();
            glShaderSource(shaderId, 1, &i, nullptr);
            glCompileShader(shaderId);

            errorHandling("Shader Id: " + std::to_string(shaderId));

            return shaderId;
        }

    void Shader::checkError(const std::string shaderIdentifier){
        errorHandling(shaderIdentifier);
    }

    unsigned int Shader::getShaderId() const{
        return shaderId;
    }
