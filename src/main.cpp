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

void errorHandling (GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar *message,
            const void *userParam){

            std::cout << "error !! \n";

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

    float positoins[] = {
        0.0f, 0.0f, 1.0f,           1.0f, 1.0f,
        -1.0f, 0.0f, 1.0f,           0.0f, 1.0f,
        0.0f, -1.0f, 1.0f,         1.0f, 0.0f,
        -1.0f, -1.0f, 1.0f,          0.0f, 0.0f
    };

    unsigned int indexedPositions[] = {
        0, 1, 2, 2, 3, 1
    };

    VAO vao = VAO();
    glBindVertexArray(vao.getVaoId());

    VBO vbo = VBO();
    vbo.setData(positoins, sizeof(positoins), GL_STATIC_DRAW);

    VertexLayout vertexLayout = VertexLayout(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    vbo.attributePointer(vertexLayout);

    VertexLayout texturesLayout = VertexLayout(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*) (3*sizeof(float)));
    vbo.attributePointer(texturesLayout);



    IndexBuffer indexedBuffer = IndexBuffer(indexedPositions, sizeof(indexedPositions), GL_STATIC_DRAW);
    indexedBuffer.bindToVAO(vao.getVaoId());
    vao.setIndexCount(sizeof(indexedPositions)/sizeof(unsigned int));


    ShaderProgram basic = ShaderProgram();

    Shader vertexShader = Shader(GL_VERTEX_SHADER, fileReader("../res/shaders/vertex/basicPosition.shader"));
    basic.addShader(vertexShader);

    Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, fileReader("../res/shaders/fragment/redColoredBackground.shader"));
    basic.addShader(fragmentShader);
    basic.linkProgram();

    //---- Texture

    Texture texture = Texture(Image("../res/textures/mikasa.jpg"));
    basic.addGlUniform1i("s_texture", texture);

    //---

    float r = 0.0f;
    float inc = 0.01f;

    float rr = 0.01;

    Renderer renderer = Renderer();

    {
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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){

        /* Render here */
        renderer.clear();


        {
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 proj = glm::mat4(1.0f);

            model = glm::rotate(model, glm::radians(rr) , glm::vec3 {1.0f, 1.0f, 1.0f});
            model = glm::translate(model, glm::vec3 {1, 1, -1});
            model = glm::scale(model, glm::vec3 {3, 3, 0});

            view = glm::translate(view, glm::vec3 {0, 0, -5});

            //proj = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.0f , 5.0f);
            proj = glm::perspective(glm::radians(45.0f), (float)1080/(float)680, 0.0f, 10.0f);

            basic.addGlUniformMatrix4fv("modelMat", model);
            basic.addGlUniformMatrix4fv("viewMat", view);
            basic.addGlUniformMatrix4fv("projMat", proj);

            renderer.drawTrinanglerElement(vao, basic.getProgramId(), texture.getTexturId());

            rr += 1;
            if (rr > 360.0f)
                rr = 0.0f;

        }


        glm::vec4 color {r, 0.4f, 0.3f, 1.0f};
        basic.addGlUniform4f("u_color", color);

        if (r > 1.0f)
            inc = -inc;
        else if (r < 0.0f)
            inc = 0.01f;

        r += inc;


        {

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

        {

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

            ImGui::SliderFloat("Mikasa", &rr, 0.0f, 360.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

            ImGui::Text("Color");
            ImGui::SliderFloat("Color", &r, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f


            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }


        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        }


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

     // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
