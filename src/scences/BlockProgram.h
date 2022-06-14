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
#include "LightSource.h"

class BlockProgram : public Program {

private:
    LightSource lightSource;
    ShaderProgram basic;
    VAO vao;

    float x;
    float y;
    float z;

public:
    BlockProgram(LightSource lightSource);
    void main(const Renderer renderer, const Camera camera) override;
    void imGui() override;
    ~BlockProgram();
};

