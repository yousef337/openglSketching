#pragma once
#include "Program.h"
#include "../external/imGUI/imgui.h"
#include "../external/imGUI/imgui_impl_glfw.h"
#include "../external/imGUI/imgui_impl_opengl3.h"
#include "../fileReader.h"
#include "../ShaderProgram.h"
#include "../VBO.h"
#include "../IndexBuffer.h"
#include "../Renderer.h"
#include "../Camera.h"
#include "../external/glm/vec4.hpp"
#include "../external/glm/mat4x4.hpp"

class LightSource : public Program {

private:
    ShaderProgram basic;
    VAO vao;
    glm::mat4 lightModel;
    glm::vec4 color;
    glm::vec4 lightPos;

public:
    LightSource();
    void main(const Renderer renderer, const Camera camera) override;
    void imGui() override;
    glm::mat4 getLightModel();
    glm::vec4 getLightPos();
    glm::vec4 getLightColor();
    glm::vec4 getAmbientColor();
    glm::vec4 getDiffuseColor();
    glm::vec4 getSpecularColor();
    ~LightSource();
};


