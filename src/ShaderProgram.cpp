#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ShaderProgram {

private:
    unsigned int id;

    void errorHandling(const unsigned int shaderId, const GLenum shaderType){

        int results;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &results);

        if (results != GL_TRUE){

            int log_length = 0;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &log_length);

            char* message = (char*) alloca(log_length * sizeof(char));

            glGetShaderInfoLog(shaderId, log_length, &log_length, message);

            std::cout << (shaderType == GL_VERTEX_SHADER? "Vertex" : "Fragment") << std::endl;

            std::cout << message << std::endl;
        }
    }

public:

    ShaderProgram(){
        id = glCreateProgram();
    }

    unsigned int getProgramId(){
        return id;
    }

    unsigned int addShader(GLenum shaderType, const std::string& shaderSource){
        unsigned int shaderId = glCreateShader(shaderType);
        const char* i = shaderSource.c_str();
        glShaderSource(shaderId, 1, &i, nullptr);
        glCompileShader(shaderId);

        errorHandling(shaderId, shaderType);

        glAttachShader(id, shaderId);
        return shaderId;
    }

};
