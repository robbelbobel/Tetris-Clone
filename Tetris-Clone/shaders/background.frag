#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D backgroundTexture;

void main(){
    FragColor = texture(backgroundTexture, TexCoords);
}
