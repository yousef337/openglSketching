#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;
layout (location = 2) in vec2 texturePos;

out vec4 fragPos;
out vec4 normalVec;
out vec2 textureCoord;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main(){
    gl_Position = projMat * viewMat * modelMat * position;
    fragPos = modelMat * position;
    textureCoord = texturePos;

    normalVec = transpose(inverse(modelMat))*normal;
};

