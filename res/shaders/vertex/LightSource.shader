#version 330 core

layout (location = 0) in vec4 position;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main(){
    gl_Position = projMat * viewMat * modelMat * position;
};

