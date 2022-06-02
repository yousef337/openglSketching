#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "fileReader.cpp"
#include "ShaderProgram.cpp"
#include "VAO.cpp"
#include "VBO.cpp"
#include "Texture.cpp"
#include "IndexBuffer.cpp"
#include "Intermediate/Image.cpp"
#include "Renderer.cpp"

int main(void){

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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

    //glDebugMessageCallback(&errorHandling, );

    /*
    float positoins[] = {
        0.0f, 0.0f,
        -0.5f, 0.0f,
        0.0f, -0.5f,

        0.0f, -0.5f,
        -0.5f, -0.5f,
        -0.5f, 0.0f,
    };
    */

    float positoins[] = {
        0.0f, 0.0f,           1.0f, 1.0f,
        -0.5f, 0.0f,          0.0f, 1.0f,
        0.0f, -0.5f,          1.0f, 0.0f,
        -0.5f, -0.5f,         0.0f, 0.0f
    };

    unsigned int indexedPositions[] = {
        0, 1, 2, 2, 3, 1
    };

    VAO vao = VAO();
    glBindVertexArray(vao.getVaoId());

    VBO vbo = VBO();
    vbo.setData(positoins, sizeof(positoins), GL_STATIC_DRAW);

    VertexLayout vertexLayout = VertexLayout(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
    vbo.attributePointer(vertexLayout);

    VertexLayout texturesLayout = VertexLayout(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*) (2*sizeof(float)));
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

    Texture texture = Texture(Image("../res/textures/brick.jpg"));

    glUniform1i(glGetUniformLocation(basic.getProgramId(), "s_texture"), texture.getOffset());

    //---

    float r = 0.0f;
    float inc = 0.01f;


    Renderer renderer = Renderer();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){

        /* Render here */
        renderer.clear();

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        renderer.drawTrinanglerElement(vao, basic.getProgramId(), texture.getTexturId());

        glUniform4f(glGetUniformLocation(basic.getProgramId(), "u_color"), r, 0.4f, 0.3f, 1.0f);

        if (r > 1.0f)
            inc = -inc;
        else if (r < 0.0f)
            inc = 0.01f;

        r += inc;


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
