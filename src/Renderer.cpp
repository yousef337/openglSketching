#include "Renderer.h"

    void Renderer::clear(){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::drawTrinanglerElement(VAO vao, unsigned int shaderProgramId, unsigned int texturId) const{
        glBindVertexArray(vao.getVaoId());
        glUseProgram(shaderProgramId);
        glBindTexture(GL_TEXTURE_2D, texturId);
        glActiveTexture(GL_TEXTURE0);
        glDrawElements(GL_TRIANGLES, vao.getIndexCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::drawTrinanglerElement(VAO vao, unsigned int shaderProgramId) const{
        glBindVertexArray(vao.getVaoId());
        glUseProgram(shaderProgramId);
        glDrawElements(GL_TRIANGLES, vao.getIndexCount(), GL_UNSIGNED_INT, nullptr);
    }


