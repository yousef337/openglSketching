#include "BlockProgram.h"

BlockProgram::BlockProgram(LightSource lightSource){

        this->lightSource = lightSource;
        x = 10.0f;
        y = 3.0f;
        z = -15.0f;

        float positoins[] = {
         //back                         // need to be verfied normals
        0.0f, 0.0f, 1.0f,     1.0f, 1.0f,           0.0f, 0.0f, -1.0f,
        -1.0f, 0.0f, 1.0f,    0.0f, 1.0f,         0.0f, 0.0f, -1.0f,
        0.0f, -1.0f, 1.0f,    1.0f, 0.0f,         0.0f, 0.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,   0.0f, 0.0f,          0.0f, 0.0f, -1.0f,

        //Right
        0.0f, 0.0f, 2.0f,      0.0f, 1.0f,            1.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 2.0f,     0.0f, 0.0f,           1.0f, 0.0f, 0.0f,

        //front
        0.0f, 0.0f, 2.0f,      1.0f, 1.0f,            0.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, 2.0f,     0.0f, 1.0f,           0.0f, 0.0f, 1.0f,
        0.0f, -1.0f, 2.0f,     1.0f, 0.0f,            0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 2.0f,    0.0f, 0.0f,              0.0f, 0.0f, 1.0f,

        // upper
        0.0f, 0.0f, 2.0f,    1.0f, 0.0f,            0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, 1.0f,   0.0f, 1.0f,              0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, 2.0f,   0.0f, 0.0f,               0.0f, 1.0f, 0.0f,

        //left
        -1.0f, 0.0f, 2.0f,     1.0f, 1.0f,          -1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 2.0f,     1.0f, 0.0f,        -1.0f, 0.0f, 0.0f,

        //bottom
         0.0f, -1.0f, 2.0f,   1.0f, 1.0f,           0.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 2.0f,   0.0f, 1.0f,          0.0f, -1.0f, 0.0f,

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

    VertexLayout vertexLayout = VertexLayout(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);
    vbo.attributePointer(vertexLayout);

    VertexLayout vertexLayoutNorm = VertexLayout(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*) (5 * sizeof(float)));
    vbo.attributePointer(vertexLayoutNorm);


    VertexLayout vertexLayoutTextureCords = VertexLayout(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*) (3 * sizeof(float)));
    vbo.attributePointer(vertexLayoutTextureCords);


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

    //---- Texture

    texture = ImagedTexture(Image("../res/textures/brick.jpg"));
    basic.addGlUniform1i("material.diffuseMap", texture);

}

void BlockProgram::main(const Renderer renderer, const Camera camera){

    {
            glm::mat4 model = glm::mat4(1.0f);

            model = glm::rotate(model, glm::radians(0.0f) , glm::vec3 {1.0f, 1.0f, 1.0f});
            //x += 0.001f;
            model = glm::translate(model, glm::vec3 {x, y, z});
            model = glm::scale(model, glm::vec3 {9, 1, 13});

            basic.addGlUniformMatrix4fv("modelMat", model);
            basic.addGlUniformMatrix4fv("viewMat", camera.getViewMatrix());
            basic.addGlUniformMatrix4fv("projMat", camera.getProjMatrix());

            //basic.addGlUniform4f("material.ambient", glm::vec4(0.1f, 0.2f, 0.1f, 1.0f));
            //basic.addGlUniform4f("material.diffuse", glm::vec4(0.7f, 0.5f, 0.6f, 1.0f));
            basic.addGlUniform4f("material.specular", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
            basic.addGLUniform1f("material.specShininess", 32);

            
            basic.addGlUniform4f("light.ambient", lightSource.getAmbientColor());
            basic.addGlUniform4f("light.diffuse", lightSource.getDiffuseColor());
            basic.addGlUniform4f("light.specular", lightSource.getSpecularColor());


            
            basic.addGLUniform1f("light.constantTerm", 0.1f);
            basic.addGLUniform1f("light.linearTerm", 0.03f);
            basic.addGLUniform1f("light.quadraticTerm", 0.02f);



            basic.addGlUniform4f("lightColor", lightSource.getLightColor());
            basic.addGlUniformMatrix4fv("lightModel", lightSource.getLightModel());
            basic.addGlUniform4f("light.lightPos", lightSource.getLightPos());

            basic.addGlUniform4f("viewPos", glm::vec4{camera.getCameraPos(), 0.0f});

            renderer.drawTrinanglerElement(vao, basic.getProgramId(), texture.getTexturId());

        }


        glm::vec4 color {0.1f, 0.4f, 0.3f, 1.0f};
        basic.addGlUniform4f("u_color", color);

}


void BlockProgram::imGui(){
    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("x");               // Display some text (you can use a format strings too)

    ImGui::SliderFloat("x", &x, -20.0f, 20.0f);          // Edit 1 float using a slider from 0.0f to 1.0f

    ImGui::Text("y");
    ImGui::SliderFloat("y", &y, -20.0f, 20.0f);        // Edit 1 float using a slider from 0.0f to 1.0f
    
    ImGui::Text("z");
    ImGui::SliderFloat("z", &z, -20.0f, 20.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

    ImGui::End();
}


BlockProgram::~BlockProgram(){

}

