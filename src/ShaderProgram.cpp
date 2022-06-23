#include "ShaderProgram.h"

    ShaderProgram::ShaderProgram(){
        programId = glCreateProgram();
    }

    unsigned int  ShaderProgram::getProgramId() const{
        return programId;
    }

    void ShaderProgram::addShader(const Shader& shader){
        glAttachShader(programId, shader.getShaderId());
    }

    void ShaderProgram::linkProgram(){
        glLinkProgram(programId);
    }

    void ShaderProgram::addGLUniform1f(const char* name, const float value){
        glUseProgram(programId);
        glUniform1f(glGetUniformLocation(programId, name), value);
        glUseProgram(0);

    }

    void  ShaderProgram::addGlUniform4f(const char* name, const glm::vec4& vec){
        glUseProgram(programId);
        glUniform4f(glGetUniformLocation(programId, name), vec.x, vec.y, vec.z, vec.w);
        glUseProgram(0);
    }

    void  ShaderProgram::addGlUniform1i(const char* name, const Texture& texture){
        glUseProgram(programId);
        glUniform1i(glGetUniformLocation(programId, name), texture.getOffset());
        glUseProgram(0);
    }


    void  ShaderProgram::addGlUniformMatrix4fv(const char* name, const glm::mat4& matrix){
        glUseProgram(programId);
        glUniformMatrix4fv(glGetUniformLocation(programId, name),1, GL_FALSE,  glm::value_ptr(matrix));
        glUseProgram(0);
    }
