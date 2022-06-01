#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "fileReader.cpp"
#include "ShaderProgram.cpp"

int main(void){

    fileReader("../res/shaders/vertex/basicPosition.shader");

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
        0.0f, 0.0f,
        -0.5f, 0.0f,
        0.0f, -0.5f,
        -0.5f, -0.5f,
    };

    unsigned int indexedPositions[] = {
        0, 1, 2, 2, 3, 1
    };

    unsigned int vao;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positoins), positoins, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
    glEnableVertexAttribArray(0);

    unsigned int indexedBuffer;
    glGenBuffers(1, &indexedBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexedBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexedPositions), indexedPositions, GL_STATIC_DRAW);


    ShaderProgram basic = ShaderProgram();
    basic.addShader(GL_VERTEX_SHADER, fileReader("../res/shaders/vertex/basicPosition.shader"));
    unsigned int aid = basic.addShader(GL_FRAGMENT_SHADER, fileReader("../res/shaders/fragment/redColoredBackground.shader"));

    glLinkProgram(basic.getProgramId());
    glUseProgram(basic.getProgramId());

    float r = 0.0f;
    float inc = 0.01f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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
