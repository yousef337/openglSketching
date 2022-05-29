#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "fileReader.cpp"
#include "ShaderProgram.cpp"

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader){


    return 0;
}


int main(void){

    fileReader("../res/shaders/vertex/basicPosition.shader");

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

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

    float positoins[6] = {
        -0.5f,0.0f,
        0.5f,1.0f,
        0.0f,-0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positoins), positoins, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
    glEnableVertexAttribArray(0);

    ShaderProgram basic = ShaderProgram();
    basic.addShader(GL_VERTEX_SHADER, fileReader("../res/shaders/vertex/basicPosition.shader"));
    basic.addShader(GL_FRAGMENT_SHADER, fileReader("../res/shaders/fragment/redColoredBackground.shader"));

    glLinkProgram(basic.getProgramId());
    glUseProgram(basic.getProgramId());

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);



        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
