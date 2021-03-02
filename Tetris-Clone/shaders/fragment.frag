#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D fragmentTexture;

uniform vec3 color;

void main(){
    FragColor = mix(texture(fragmentTexture, TexCoords), vec4(color, 1.0f), 0.5f);
}
