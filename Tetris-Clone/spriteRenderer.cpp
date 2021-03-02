//
//  spriteRenderer.cpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 28/02/2021.
//

#include "spriteRenderer.hpp"

void SpriteRenderer::renderFragment(Fragment fragment, glm::mat4 model){
    // Get Fragment Color
    glm::vec3 color;
    switch(fragment.color){
        case AQUA:
            color = glm::vec3(0.0f, 1.0f, 1.0f);
            break;
        case YELLOW:
            color = glm::vec3(1.0f, 1.0f, 0.0f);
            break;
        case PURPLE:
            color = glm::vec3(0.5f, 0.0f, 0.5f);
            break;
        case GREEN:
            color = glm::vec3(0.0f, 1.0f, 0.0f);
            break;
        case RED:
            color = glm::vec3(1.0f, 0.0f, 0.0f);
            break;
        case BLUE:
            color = glm::vec3(0.0f, 0.0f, 1.0f);
            break;
        case ORANGE:
            color = glm::vec3(1.0f, 0.65, 0.0f);
            break;
        case WHITE:
            color = glm::vec3(1.0f, 1.0f, 1.0f);
        default:
            color = glm::vec3(0.0f);
    }
    
    // Set Fragment Color
    SpriteRenderer::fragmentShader.setVec3("color", color);
    
    // Set Model Matrix
    SpriteRenderer::fragmentShader.setMat4("model", model);
    
    // Draw The Fragment (2*Triangles => 6 vertices)
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

SpriteRenderer::SpriteRenderer() : fragmentShader("/Users/robbetiteca/projects/Tetris-Clone/Tetris-Clone/shaders/fragment.vert", "/Users/robbetiteca/projects/Tetris-Clone/Tetris-Clone/shaders/fragment.frag"), backgroundShader("/Users/robbetiteca/projects/Tetris-Clone/Tetris-Clone/shaders/background.vert", "/Users/robbetiteca/projects/Tetris-Clone/Tetris-Clone/shaders/background.frag")
{
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

int SpriteRenderer::loadTexture(std::string path){
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
    
    SpriteRenderer::textures.push_back(texID);
    
    return (int) (SpriteRenderer::textures.size() - 1);
}

void SpriteRenderer::renderBoard(unsigned int texIndex, GameBoard board, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    SpriteRenderer::fragmentShader.use();
    SpriteRenderer::fragmentShader.setInt("fragmentTexture", 0);
    SpriteRenderer::fragmentShader.setMat4("projection", glm::ortho(0.0f, (float) SCR_WIDTH, (float) SCR_HEIGHT, 0.0f, -1.0f, 1.0f));
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, SpriteRenderer::textures[texIndex]);
    
    glBindVertexArray(SpriteRenderer::VAO);
    
    int fragmentSize = floor(SpriteRenderer::fragmentSizeRatio * SCR_HEIGHT);
    
    int UI_margin_x = floor(SpriteRenderer::UI_marginRatio_x * SCR_WIDTH) - (fragmentSize * board.width)/2;
    int UI_margin_y = floor(SpriteRenderer::UI_marginRatio_y * SCR_HEIGHT) - (fragmentSize * board.height)/2;
    
    for(unsigned int y = 0; y < board.layout.size(); y++){
        for(unsigned int x = 0; x < board.layout[y].size(); x++){
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(UI_margin_x + x * fragmentSize, UI_margin_y + (board.height - y) * fragmentSize, 0));
            model = glm::scale(model, glm::vec3(fragmentSize));
            
            SpriteRenderer::renderFragment(board.layout[y][x], model);
        }
    }
}

void SpriteRenderer::renderBackground(unsigned int texIndex, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    glm::mat4 model = glm::mat4(1.0f);
    
    float scaleY = SCR_WIDTH;
    float scaleX = (16.0f/9.0f) * SCR_WIDTH;
    
    model = glm::scale(model, glm::vec3(scaleX, scaleY, 1.0f));
    
    SpriteRenderer::backgroundShader.use();
    SpriteRenderer::backgroundShader.setMat4("projection", glm::ortho(0.0f, (float) SCR_WIDTH, (float) SCR_HEIGHT, 0.0f, -1.0f, 1.0f));
    SpriteRenderer::backgroundShader.setMat4("model", model);
    
    SpriteRenderer::backgroundShader.setInt("backgroundTexture", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, SpriteRenderer::textures[texIndex]);
    
    glBindVertexArray(SpriteRenderer::VAO);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
}

void SpriteRenderer::renderTetromino(unsigned int texIndex, Tetromino* tetromino, GameBoard board, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    SpriteRenderer::fragmentShader.use();
    SpriteRenderer::fragmentShader.setInt("fragmentTexture", 0);
    SpriteRenderer::fragmentShader.setMat4("projection", glm::ortho(0.0f, (float) SCR_WIDTH, (float) SCR_HEIGHT, 0.0f, -1.0f, 1.0f));
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, SpriteRenderer::textures[texIndex]);
    
    glBindVertexArray(SpriteRenderer::VAO);
    
    int fragmentSize = floor(SpriteRenderer::fragmentSizeRatio * SCR_HEIGHT);
    
    int UI_margin_x = floor(SpriteRenderer::UI_marginRatio_x * SCR_WIDTH) - (fragmentSize * board.width)/2;
    int UI_margin_y = floor(SpriteRenderer::UI_marginRatio_y * SCR_HEIGHT) - (fragmentSize * board.height)/2;
    
    for(unsigned int i = 0; i < tetromino->rotations[tetromino->a_rot].fragments.size(); i++){
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(UI_margin_x + (tetromino->rotations[tetromino->a_rot].fragments[i].p_x + tetromino->posX) * fragmentSize, UI_margin_y + (board.height - (tetromino->rotations[tetromino->a_rot].fragments[i].p_y + tetromino->posY)) * fragmentSize, 0));
        model = glm::scale(model, glm::vec3(fragmentSize));
        
        SpriteRenderer::renderFragment(tetromino->rotations[tetromino->a_rot].fragments[i], model);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}
