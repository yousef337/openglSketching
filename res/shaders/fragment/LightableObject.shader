#version 330 core

layout (location = 0) out vec4 color;

in vec4 normalVec;
in vec4 fragPos;
in vec2 textureCoord;

struct Material {
    sampler2D diffuseMap;
    vec4 specular;
    float specShininess;
}; 

struct Light {

    vec4 lightPos;


    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

    float constantTerm;
    float linearTerm;
    float quadraticTerm;

};

uniform Material material;
uniform Light light;

uniform vec4 lightColor;
uniform mat4 lightModel;

uniform vec4 viewPos;

uniform vec4 u_color;


void main(){
    // Ambient light
   vec4 ambientLight = vec4(texture(material.diffuseMap, textureCoord)) * light.ambient;

    // Diffuse light
   vec4 norm = normalize(normalVec);
   vec4 lightDir = normalize(light.lightPos - fragPos);

   float diff = max(dot(lightDir, norm), 0.0);

   vec4 diffuseLight = (diff * vec4(texture(material.diffuseMap, textureCoord))) * light.diffuse;

   // Specular Light
   vec4 viewDir = normalize(viewPos - fragPos);
   vec4 reflectedLightDir = reflect(-lightDir, norm);

   float spec = pow(max(dot(viewDir, reflectedLightDir), 0), material.specShininess);
   vec4 specularLight = material.specular * spec * light.specular;

    // Calculate attenuation 
    float distance = length(light.lightPos - fragPos);
    float attenuation = 1/(light.constantTerm + light.linearTerm*distance + distance*distance*light.quadraticTerm);

   color = (ambientLight + diffuseLight + specularLight) * attenuation;
};

