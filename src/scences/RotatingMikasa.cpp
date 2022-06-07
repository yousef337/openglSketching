#include "RotatingMikasa.h"


RotatingMikasa::RotatingMikasa() {
    std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAa \n";

    r = 0.0f;
    rr = 0.0f;
    inc = 0.0f;

     float positoins[] = {
        0.0f, 0.0f, 1.0f,           1.0f, 1.0f,
        -1.0f, 0.0f, 1.0f,           0.0f, 1.0f,
        0.0f, -1.0f, 1.0f,         1.0f, 0.0f,
        -1.0f, -1.0f, 1.0f,          0.0f, 0.0f
    };

    unsigned int indexedPositions[] = {
        0, 1, 2, 2, 3, 1
    };

    vao = VAO();
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


    basic = ShaderProgram();

    Shader vertexShader = Shader(GL_VERTEX_SHADER, fileReader("../res/shaders/vertex/basicPosition.shader"));
    basic.addShader(vertexShader);

    Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, fileReader("../res/shaders/fragment/redColoredBackground.shader"));
    basic.addShader(fragmentShader);
    basic.linkProgram();

    //---- Texture

    texture = Texture(Image("../res/textures/mikasa.jpg"));
    basic.addGlUniform1i("s_texture", texture);

}


void RotatingMikasa::main(Renderer renderer){

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


}


void RotatingMikasa::imGui(){
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

    ImGui::SliderFloat("Mikasa", &rr, 0.0f, 360.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

    ImGui::Text("Color");
    ImGui::SliderFloat("Color", &r, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f


    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

RotatingMikasa::~RotatingMikasa(){

}

