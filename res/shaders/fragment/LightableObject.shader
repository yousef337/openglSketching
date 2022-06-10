#version 330 core

layout (location = 0) out vec4 color;

in vec4 normalVec;
in vec4 fragPos;

uniform vec4 lightColor;
uniform vec4 lightPos;
uniform mat4 lightModel;

uniform vec4 viewPos;

uniform vec4 u_color;


void main(){
    // Ambient light
    float ambientStrength = 0.2;
    vec4 ambientLight = ambientStrength * lightColor;

    // Diffuse light
    vec4 norm = normalize(normalVec);
    vec4 lightDir = normalize(lightPos - fragPos);

    float diff = max(dot(lightDir, norm), 0.0);

    vec4 diffuseLight = diff * lightColor;

    // Specular Light
    float specularStrength = 0.5;
    vec4 viewDir = normalize(viewPos - fragPos);
    vec4 reflectedLightDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectedLightDir), 0), 9812);
    vec4 specularLight = spec * specularStrength * lightColor;

    color = (ambientLight + diffuseLight + specularLight) * u_color;
};

