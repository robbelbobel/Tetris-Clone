#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D genericTex;

void main(){
    
    if(texture(genericTex, TexCoords).a != 1.0f){
        discard;
    }
    
    FragColor = texture(genericTex, TexCoords);
}
