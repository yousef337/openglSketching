#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texturePos;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec2 textureCoord;

void main(){
    gl_Position = projMat * viewMat * modelMat * position;
    textureCoord = texturePos;
};
