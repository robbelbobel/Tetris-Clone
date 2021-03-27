#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D Texture;

void main(){
    
    if(texture(Texture, TexCoords).a != 1.0f){
        discard;
    }
    
    FragColor = texture(Texture, TexCoords);
}
