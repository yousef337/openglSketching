#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texturePos;

out vec2 textureCoord;

void main(){
    gl_Position = position;
    textureCoord = texturePos;
};
