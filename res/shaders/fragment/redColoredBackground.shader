#version 330 core

layout (location = 0) out vec4 color;

in vec2 textureCoord;

uniform vec4 u_color;

uniform sampler2D s_texture;

void main(){
    color = mix(texture(s_texture, textureCoord), u_color, .40);
};
