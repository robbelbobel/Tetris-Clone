//
//  spriteRenderer.cpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 28/02/2021.
//

#include "spriteRenderer.hpp"

SpriteRenderer::SpriteRenderer(){
    // Vertices
    const float vertices[] = {
        // ----POS----  ----TEX----
        0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        
        1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f
    };
    
    // Create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(SpriteRenderer::VAO);
    
    // Create VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, SpriteRenderer::VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Position Pointer
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
    // Texture Coords Pointer
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) (2 * sizeof(float)));
    
    // Bind empty buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Texture* SpriteRenderer::loadTexture(std::string path){
    //---LOAD TEXTURE---
    unsigned int texID;
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, NULL);
    
    if(!data){
        std::cout << "Couldn't load asset at path: " << path << std::endl;
    }
    
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    Texture* texture = new Texture;
    texture->ID = texID;
    texture->width = width;
    texture->height = height;
    texture->nrChannels = nrChannels;
    
    return texture;
}

void SpriteRenderer::renderTexture(Shader* shader, Texture* texture, glm::mat4 model, glm::mat4 projection){
    shader->use();
    shader->setMat4("projection", projection);
    shader->setMat4("model", model);
    
    shader->setInt("Texture", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->ID);
    
    glBindVertexArray(SpriteRenderer::VAO);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void SpriteRenderer::renderFragmentArray(Shader* shader, std::vector<Fragment*> fragments, Texture* texture, std::vector<glm::mat4> models, std::vector<glm::mat4> projections){
    shader->use();
    
    shader->setInt("Texture", 0);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->ID);
    
    glBindVertexArray(SpriteRenderer::VAO);
    
    for(unsigned int i = 0; i < fragments.size(); i++){
        // Get Fragment Color
        glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);
        
        switch(fragments[i]->color){
            case AQUA:{
                color = glm::vec3(0.0f, 1.0f, 1.0f);
                break;
            }
            case YELLOW:{
                color = glm::vec3(1.0f, 1.0f, 0.0f);
                break;
            }
            case PURPLE:{
                color = glm::vec3(0.5f, 0.0f, 0.5f);
                break;
            }
            case GREEN:{
                color = glm::vec3(0.0f, 1.0f, 0.0f);
                break;
            }
            case RED:{
                color = glm::vec3(1.0f, 0.0f, 0.0f);
                break;
            }
            case PINK:{
                color = glm::vec3(0.87, 0.12f, 0.74f);
                break;
            }
            case ORANGE:{
                color = glm::vec3(1.0f, 0.65, 0.0f);
                break;
            }
            case WHITE:{
                color = glm::vec3(0.5f);
                break;
            }
            default:{
                color = glm::vec3(0.0f);
                std::cout << "Unknown color for fragment! Color: " << fragments[i]->color << std::endl;
            }
        }
        
        shader->setVec3("color", color);
        shader->setMat4("model", models[i]);
        shader->setMat4("projection", projections[i]);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

void SpriteRenderer::renderTextureArray(Shader* shader, std::vector<Texture*> textures, std::vector<glm::mat4> models, std::vector<glm::mat4> projections){
    shader->use();
    
    shader->setInt("Texture", 0);
    glActiveTexture(GL_TEXTURE0);
    
    glBindVertexArray(SpriteRenderer::VAO);
    
    for(unsigned int i = 0; i < textures.size(); i++){
        shader->setMat4("model", models[i]);
        shader->setMat4("projection", projections[i]);
        
        glBindTexture(GL_TEXTURE_2D, textures[i]->ID);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}
