#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex> &verticies, const std::vector<unsigned int> &indicies, const std::vector<Texture> &textures){

    this->verticies = verticies;
    this->indicies = indicies;
    this->textures = textures;
    this->vao = VAO();
    this->vbo = VBO();
    this->indiciesBuffer = IndexBuffer();
    setupMesh();


}


void Mesh::setupMesh(){

    glBindVertexArray(vao.getVaoId());
    vbo.setData(&verticies[0], verticies.size()*sizeof(Vertex), GL_STATIC_DRAW);

    indiciesBuffer.setData(&indicies[0], indicies.size()*sizeof(unsigned int), GL_STATIC_DRAW);

    VertexLayout positions = VertexLayout(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
    VertexLayout normals = VertexLayout(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normals));
    VertexLayout textures = VertexLayout(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, textureCords));

    vbo.attributePointer(positions);
    vbo.attributePointer(normals);
    vbo.attributePointer(textures);

}

//#TODO complete the draw method
void Mesh::Draw(const Shader &shader){



}
