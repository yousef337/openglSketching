#version 330 core

layout (location = 0) out vec4 color;

in vec4 normalVec;
in vec4 fragPos;

struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float specShininess;
}; 

struct Light {

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

};

uniform Material material;
uniform Light light;

uniform vec4 lightColor;
uniform vec4 lightPos;
uniform mat4 lightModel;

uniform vec4 viewPos;

uniform vec4 u_color;


void main(){
    // Ambient light
    vec4 ambientLight =  material.ambient * light.ambient;

    // Diffuse light
    vec4 norm = normalize(normalVec);
    vec4 lightDir = normalize(lightPos - fragPos);

    float diff = max(dot(lightDir, norm), 0.0);

    vec4 diffuseLight = (diff * material.diffuse) * light.diffuse;

    // Specular Light
    vec4 viewDir = normalize(viewPos - fragPos);
    vec4 reflectedLightDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectedLightDir), 0), material.specShininess);
    vec4 specularLight = material.specular * spec * light.specular;

    color = (ambientLight + diffuseLight + specularLight) * u_color;
};

