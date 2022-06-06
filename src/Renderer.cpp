#include "Renderer.h"

    void Renderer::clear(){
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::drawTrinanglerElement(VAO vao, unsigned int shaderProgramId, unsigned int texturId){
        glBindVertexArray(vao.getVaoId());
        glUseProgram(shaderProgramId);
        glBindTexture(GL_TEXTURE_2D, texturId);
        glDrawElements(GL_TRIANGLES, vao.getIndexCount(), GL_UNSIGNED_INT, nullptr);
    }
