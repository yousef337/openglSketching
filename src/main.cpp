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
#include "scences/BlockProgram.h"
#include "scences/LightSource.h"
#include "scences/Program.h"
#include "Camera.h"

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

void assistentFrameSetup(RotatingMikasa program){
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

float width = 1560;
float height = 880;
Camera camera = Camera(width, height);
float lastMouseX = 0.0f;
float lastMouseY = 0.0f;
float yawAngle = 0.0f;
float pitchAngle = 0.0f;
bool firstMove = true;

void mouseCallback(GLFWwindow* window, double xpos, double ypos){

    if (firstMove){
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstMove = false;
    }

    float xOffset = xpos - lastMouseX;
    float yOffset = lastMouseY - ypos;

    lastMouseX = xpos;
    lastMouseY = ypos;

    const float sensitivity = 0.2f;

    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yawAngle += xOffset;
    pitchAngle += yOffset;

    if(pitchAngle > 89.0f)
        pitchAngle = 89.0f;
    if(pitchAngle < -89.0f)
        pitchAngle = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yawAngle)) * cos(glm::radians(pitchAngle));
    direction.y = sin(glm::radians(pitchAngle));
    direction.z = sin(glm::radians(yawAngle)) * cos(glm::radians(pitchAngle));
    camera.setPointingPosition(glm::normalize(direction));

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
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    assistentWindowSetup(window);

    Renderer renderer = Renderer();
    RotatingMikasa rm = RotatingMikasa();
    LightSource ls = LightSource();
    BlockProgram bp = BlockProgram(ls);

    glfwSetCursorPosCallback(window, mouseCallback);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){

        renderer.clear();


        rm.main(renderer, camera);
        bp.main(renderer, camera);
        ls.main(renderer, camera);

        assistentFrameSetup(rm);

        camera.keyboardProcessing(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    assistentCleanSetup();

    glfwTerminate();
    return 0;
}
