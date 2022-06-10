#include "LightSource.h"


LightSource::LightSource(){

    lightPos = glm::vec4 {5, 5, -1, 0};
    color =  {1.0f, 1.0f, 1.0f, 1.0f};

    //TODO Fix the redundancy

        float positoins[] = {
         //back
        0.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, 1.0f,
        0.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        //Right
        0.0f, 0.0f, 2.0f,
        0.0f, -1.0f, 2.0f,

        //front
        0.0f, 0.0f, 2.0f,
        -1.0f, 0.0f, 2.0f,
        0.0f, -1.0f, 2.0f,
        -1.0f, -1.0f, 2.0f,

        // upper
        0.0f, 0.0f, 2.0f,
        -1.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, 2.0f,

        //left
        -1.0f, 0.0f, 2.0f,
        -1.0f, -1.0f, 2.0f,

        //bottom
         0.0f, -1.0f, 2.0f,
        -1.0f, -1.0f, 2.0f

    };


    unsigned int indexedPositions[] = {
        0, 1, 2, 2, 3, 1, // rear
        0, 4, 2, 2, 5, 4, // front
        6, 7, 8, 8, 9, 7, // right
        0, 10, 12, 12, 11, 0, // upper
        13, 1, 14, 14, 3, 1, // left
        15, 2, 3, 3, 16, 15 //bottom

    };

    vao = VAO();
    glBindVertexArray(vao.getVaoId());

    VBO vbo = VBO();
    vbo.setData(positoins, sizeof(positoins), GL_STATIC_DRAW);

    VertexLayout vertexLayout = VertexLayout(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
    vbo.attributePointer(vertexLayout);

    IndexBuffer indexedBuffer = IndexBuffer(indexedPositions, sizeof(indexedPositions), GL_STATIC_DRAW);
    indexedBuffer.bindToVAO(vao.getVaoId());
    vao.setIndexCount(sizeof(indexedPositions)/sizeof(unsigned int));


    basic = ShaderProgram();

    Shader vertexShader = Shader(GL_VERTEX_SHADER, fileReader("../res/shaders/vertex/LightSource.shader"));
    basic.addShader(vertexShader);

    Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, fileReader("../res/shaders/fragment/LightSource.shader"));
    basic.addShader(fragmentShader);
    basic.linkProgram();

}

void LightSource::main(const Renderer renderer, const Camera camera){

        {
            lightModel = glm::mat4(1.0f);


            lightModel = glm::translate(lightModel, glm::vec3 {lightPos.x, lightPos.y, lightPos.z});
            lightModel = glm::rotate(lightModel, glm::radians(0.0f) , glm::vec3 {1.0f, 1.0f, 1.0f});
            lightModel = glm::scale(lightModel, glm::vec3 {1, 1, 1});

            basic.addGlUniformMatrix4fv("modelMat", lightModel);
            basic.addGlUniformMatrix4fv("viewMat", camera.getViewMatrix());
            basic.addGlUniformMatrix4fv("projMat", camera.getProjMatrix());

            renderer.drawTrinanglerElement(vao, basic.getProgramId());

        }

        basic.addGlUniform4f("u_color", color);
}

glm::vec4 LightSource::getLightColor(){
    return color;
}

glm::mat4 LightSource::getLightModel(){
    return lightModel;
}

glm::vec4 LightSource::getLightPos(){
    return lightPos;
}



void LightSource::imGui(){
}

LightSource::~LightSource() {
}


