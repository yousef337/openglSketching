#include "BlockProgram.h"

BlockProgram::BlockProgram(LightSource lightSource){

        this->lightSource = lightSource;

        float positoins[] = {
         //back                         // need to be verfied normals
        0.0f, 0.0f, 1.0f,                0.0f, 0.0f, -1.0f,
        -1.0f, 0.0f, 1.0f,              0.0f, 0.0f, -1.0f,
        0.0f, -1.0f, 1.0f,               0.0f, 0.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,                0.0f, 0.0f, -1.0f,

        //Right
        0.0f, 0.0f, 2.0f,                 1.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 2.0f,                1.0f, 0.0f, 0.0f,

        //front
        0.0f, 0.0f, 2.0f,                  0.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, 2.0f,                0.0f, 0.0f, 1.0f,
        0.0f, -1.0f, 2.0f,                 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 2.0f,                  0.0f, 0.0f, 1.0f,

        // upper
        0.0f, 0.0f, 2.0f,                0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, 1.0f,                 0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, 2.0f,                    0.0f, 1.0f, 0.0f,

        //left
        -1.0f, 0.0f, 2.0f,             -1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 2.0f,            -1.0f, 0.0f, 0.0f,

        //bottom
         0.0f, -1.0f, 2.0f,              0.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 2.0f,             0.0f, -1.0f, 0.0f,

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

    VertexLayout vertexLayout = VertexLayout(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), 0);
    vbo.attributePointer(vertexLayout);

    VertexLayout vertexLayoutNorm = VertexLayout(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*) (3 * sizeof(float)));
    vbo.attributePointer(vertexLayoutNorm);

    IndexBuffer indexedBuffer = IndexBuffer(indexedPositions, sizeof(indexedPositions), GL_STATIC_DRAW);
    indexedBuffer.bindToVAO(vao.getVaoId());
    vao.setIndexCount(sizeof(indexedPositions)/sizeof(unsigned int));


    basic = ShaderProgram();

    Shader vertexShader = Shader(GL_VERTEX_SHADER, fileReader("../res/shaders/vertex/LightableObject.shader"));
    basic.addShader(vertexShader);

    Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, fileReader("../res/shaders/fragment/LightableObject.shader"));
    basic.addShader(fragmentShader);
    basic.linkProgram();


    glm::vec4 ambientLightSource {1.0f, 1.0f, 1.0f, 1.0f};
    basic.addGlUniform4f("lightColor", ambientLightSource);

}

void BlockProgram::main(const Renderer renderer, const Camera camera){

    {
            glm::mat4 model = glm::mat4(1.0f);

            model = glm::rotate(model, glm::radians(0.0f) , glm::vec3 {1.0f, 1.0f, 1.0f});

            model = glm::translate(model, glm::vec3 {3, 3, -1});
            model = glm::scale(model, glm::vec3 {1, 1, 1});

            basic.addGlUniformMatrix4fv("modelMat", model);
            basic.addGlUniformMatrix4fv("viewMat", camera.getViewMatrix());
            basic.addGlUniformMatrix4fv("projMat", camera.getProjMatrix());

            basic.addGlUniform4f("lightColor", lightSource.getLightColor());
            basic.addGlUniformMatrix4fv("lightModel", lightSource.getLightModel());
            basic.addGlUniform4f("lightPos", lightSource.getLightPos());

            renderer.drawTrinanglerElement(vao, basic.getProgramId());

        }

        glm::vec4 color {0.1f, 0.4f, 0.3f, 1.0f};
        basic.addGlUniform4f("u_color", color);

}


void BlockProgram::imGui(){
}


BlockProgram::~BlockProgram(){

}

