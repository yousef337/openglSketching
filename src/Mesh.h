#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "external/glm/vec4.hpp"
#include "external/glm/mat4x4.hpp"
#include <string>
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "VertexLayout.h"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "Texture.h"

struct Vertex {
    glm::vec4 positions;
    glm::vec4 normals;
    glm::vec4 textureCords;
};

class Mesh {

private:
    std::vector<Vertex> verticies;
    std::vector<unsigned int> indicies;
    std::vector<Texture> textures;

    VAO vao;
    VBO vbo;
    IndexBuffer indiciesBuffer;

    void setupMesh();


public:
    Mesh(const std::vector<Vertex> &verticies, const std::vector<unsigned int> &indexedPositions, const std::vector<Texture> &textures );
    void Draw(const Shader &shader);

};