#include "external/imGUI/imgui.h"
#include "external/imGUI/imgui_impl_glfw.h"
#include "external/imGUI/imgui_impl_opengl3.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "fileReader.h"
#include "ShaderProgram.h"
#include "VBO.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "external/glm/vec4.hpp"
#include "external/glm/mat4x4.hpp"
#include "scences/RotatingMikasa.h"
#include "scences/Program.h"

void errorHandling (GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar *message,
            const void *userParam){

            std::cout << "error !! \n";

            }

void assistentWindowSetup(GLFWwindow* window){
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

}

void assistentFrameSetup(Program program){
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    program.imGui();

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void assistentCleanSetup(){
     // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

int main(void){

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1080, 680, "Hello World", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK){
        std::cout << "d/dt" << std::endl;
    }else{
        std::cout << glGetString(GL_VERSION) << std::endl;
    }

    glDebugMessageCallback(&errorHandling, (void*) 0 );

    Renderer renderer = Renderer();

    assistentWindowSetup(window);

    RotatingMikasa rm = RotatingMikasa();


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){

        renderer.clear();


        rm.main(renderer);

        assistentFrameSetup(rm);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    assistentCleanSetup();

    glfwTerminate();
    return 0;
}
