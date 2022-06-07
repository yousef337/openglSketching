#pragma once
#include "Program.h"
#include "../external/imGUI/imgui.h"
#include "../external/imGUI/imgui_impl_glfw.h"
#include "../external/imGUI/imgui_impl_opengl3.h"
#include "../fileReader.h"
#include "../ShaderProgram.h"
#include "../VBO.h"
#include "../IndexBuffer.h"
#include "../Texture.h"
#include "../Renderer.h"
#include "../external/glm/vec4.hpp"
#include "../external/glm/mat4x4.hpp"

class RotatingMikasa : public Program {

private:
    float r;
    float rr;
    float inc;
    ShaderProgram basic;
    VAO vao;
    Texture texture;

public:
    RotatingMikasa();
    void main(Renderer renderer) override;
    void imGui() override;
    ~RotatingMikasa();

};