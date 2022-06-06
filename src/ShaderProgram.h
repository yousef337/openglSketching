#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Texture.h"
#include "external/glm/vec4.hpp"
#include "external/glm/mat4x4.hpp"
#include "external/glm/gtc/type_ptr.hpp"


class ShaderProgram {

private:
    unsigned int programId;

public:

    ShaderProgram();

    unsigned int getProgramId();
    void addShader(const Shader& shader);
    void linkProgram();

    void addGlUniform4f(const char* name, const glm::vec4& vec);

    void addGlUniform1i(const char* name, const Texture& texture);


    void addGlUniformMatrix4fv(const char* name, const glm::mat4& matrix);

};

