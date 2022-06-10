#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;

out vec4 fragPos;
out vec4 normalVec;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main(){
    gl_Position = projMat * viewMat * modelMat * position;
    fragPos = modelMat * position;

    normalVec = transpose(inverse(modelMat))*normal;
};

