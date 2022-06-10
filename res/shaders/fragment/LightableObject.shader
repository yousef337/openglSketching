#version 330 core

layout (location = 0) out vec4 color;

in vec4 normalVec;
in vec4 fragPos;

uniform vec4 lightColor;
uniform vec4 lightPos;
uniform mat4 lightModel;

uniform vec4 u_color;


void main(){
    float ambientStrength = 0.2;
    vec4 ambientLight = ambientStrength * lightColor;

    vec4 norm = normalize(normalVec);
    vec4 lightDir = normalize(lightPos - fragPos);

    float diff = max(dot(lightDir, norm), 0.0);

    vec4 diffuseLight = diff * lightColor;

    color = (ambientLight + diffuseLight) * u_color;
};

