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
        case PINK:
            color = glm::vec3(0.87, 0.12f, 0.74f);
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
    SpriteRenderer::fragmentShader->setVec3("color", color);
    
    // Set Model Matrix
    SpriteRenderer::fragmentShader->setMat4("model", model);
    
    // Draw The Fragment (2*Triangles => 6 vertices)
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void SpriteRenderer::renderFrame(unsigned int texIndex, GameBoard gameBoard, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    float board_height =  (float) SpriteRenderer::fragmentSizeRatio * (float) SCR_HEIGHT * (float) gameBoard.height;
    
    float px_size = (float) board_height / ((float) SpriteRenderer::textures[texIndex].height - ((float) SpriteRenderer::totalFrameHeightMargin));
    
    float frame_height = px_size * SpriteRenderer::textures[texIndex].height;
    float frame_width  = px_size * SpriteRenderer::textures[texIndex].width;
    
    float frame_x = SpriteRenderer::Board_marginRatio_x * SCR_WIDTH  - ((float) frame_width  / 2) - px_size * ((float) SpriteRenderer::totalFrameWidthMarginLeft / 2) + px_size * ((float) SpriteRenderer::totalFrameWidthMarginRight / 2);
    float frame_y = SpriteRenderer::Board_marginRatio_y * SCR_HEIGHT - ((float) frame_height / 2) + (SpriteRenderer::totalFrameHeightMargin / 2) * px_size;

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(frame_x, frame_y, 0.0f));
    model = glm::scale(model, glm::vec3(frame_width, frame_height, 1.0f));
    
    SpriteRenderer::genericShader->use();
    SpriteRenderer::genericShader->setInt("genericTex", 0);
    SpriteRenderer::fragmentShader->setMat4("projection", glm::ortho(0.0f, (float) SCR_WIDTH, (float) SCR_HEIGHT, 0.0f, -1.0f, 1.0f));
    SpriteRenderer::fragmentShader->setMat4("model", model);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, SpriteRenderer::textures[texIndex].ID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void SpriteRenderer::renderScore(unsigned int texIndex, unsigned int score, GameBoard gameBoard, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    int digitCount = 7;
    int digits[digitCount];
    
    // Precalculate size of a single fragment
    float fragmentSize = SpriteRenderer::fragmentSizeRatio * SCR_HEIGHT;
    
    // Calculate score text width, height and clearance
    float score_width = SpriteRenderer::scoreHeightRatio * SCR_HEIGHT;
    float score_height = ((float) SpriteRenderer::textures[texIndex].height / (float) SpriteRenderer::textures[texIndex].width) * score_width;
    float score_clearance = SpriteRenderer::scoreClearanceY * score_height;
    
    // Calculate score number width, height and clearance
    float number_height = score_height;
    float number_width = ((float) SpriteRenderer::textures[SpriteRenderer::numTextures[0]].width / (float) SpriteRenderer::textures[SpriteRenderer::numTextures[0]].height) * number_height;
    float number_clearance = SpriteRenderer::numClearanceX * number_width;
    
    // Calculate score number position
    float number_x = SpriteRenderer::Board_marginRatio_x * SCR_WIDTH - (gameBoard.width / 2) * fragmentSize - SpriteRenderer::score_marginRatio_x * fragmentSize;
    float number_y = SpriteRenderer::Board_marginRatio_y * SCR_HEIGHT - (gameBoard.height / 2) * fragmentSize + number_height + score_height + score_clearance;
    
    // Calculate score text position
    float score_x = number_x - score_width;
    float score_y = number_y - number_height - score_clearance;
    
    // Convert score to seperate integers
    for(unsigned int i = 0; i < digitCount; i++){
        digits[i] = ((int) floor(score / pow(10, i))) % 10;
    }
    
    // -----Number draw loop-----
    // Start using generic shader
    SpriteRenderer::genericShader->use();
    SpriteRenderer::genericShader->setInt("genericTex", 0);
    SpriteRenderer::genericShader->setMat4("projection", glm::ortho(0.0f, (float) SCR_WIDTH, (float) SCR_HEIGHT, 0.0f, -1.0f, 1.0f));
    
    glActiveTexture(GL_TEXTURE0);
    
    for(unsigned int i = 0; i < digitCount; i++){
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(number_x - ((i + 1) * (number_width + number_clearance)), number_y, 0.0f));
        model = glm::scale(model, glm::vec3(number_width, number_height, 1.0f));
        
        // Set model uniform
        SpriteRenderer::genericShader->setMat4("model", model);
        
        // Draw the score
        glBindTexture(GL_TEXTURE_2D, SpriteRenderer::textures[SpriteRenderer::numTextures[digits[i]]].ID);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    
//    // -----Score Text Drawing-----
//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::translate(model, glm::vec3(score_x, score_y, 0.0f));
//    model = glm::scale(model, glm::vec3(score_width, score_height, 1.0f));
//
//    SpriteRenderer::genericShader->setMat4("model", model);
//
//    glBindTexture(GL_TEXTURE_2D, SpriteRenderer::textures[texIndex].ID);
//    glDrawArrays(GL_TRIANGLES, 0, 6);
}

SpriteRenderer::SpriteRenderer(){
    // Assign Shader Pointers
    SpriteRenderer::fragmentShader = new Shader("/Users/robbetiteca/projects/Tetris-Clone/Tetris-Clone/shaders/fragment.vert", "/Users/robbetiteca/projects/Tetris-Clone/Tetris-Clone/shaders/fragment.frag");
    SpriteRenderer::backgroundShader = new Shader("/Users/robbetiteca/projects/Tetris-Clone/Tetris-Clone/shaders/background.vert", "/Users/robbetiteca/projects/Tetris-Clone/Tetris-Clone/shaders/background.frag");
    SpriteRenderer::genericShader = new Shader("/Users/robbetiteca/projects/Tetris-Clone/Tetris-Clone/shaders/generic.vert", "/Users/robbetiteca/projects/Tetris-Clone/Tetris-Clone/shaders/generic.frag");
    
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
    
    Texture texture;
    texture.ID = texID;
    texture.width = width;
    texture.height = height;
    texture.nrChannels = nrChannels;
    
    SpriteRenderer::textures.push_back(texture);
    
    return (int) (SpriteRenderer::textures.size() - 1);
}

int SpriteRenderer::loadNumbers(std::string path){
    for(unsigned int i = 0; i <= 9; i++){
        SpriteRenderer::numTextures.push_back(SpriteRenderer::loadTexture(path + "/" + std::to_string(i) + ".png"));
    }
    
    return SpriteRenderer::loadTexture(path + "/score.png");
}

void SpriteRenderer::renderBoard(unsigned int texIndex, GameBoard board, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    SpriteRenderer::fragmentShader->use();
    SpriteRenderer::fragmentShader->setInt("fragmentTexture", 0);
    SpriteRenderer::fragmentShader->setMat4("projection", glm::ortho(0.0f, (float) SCR_WIDTH, (float) SCR_HEIGHT, 0.0f, -1.0f, 1.0f));
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, SpriteRenderer::textures[texIndex].ID);
    
    glBindVertexArray(SpriteRenderer::VAO);
    
    int fragmentSize = floor(SpriteRenderer::fragmentSizeRatio * SCR_HEIGHT);
    
    int UI_margin_x = floor(SpriteRenderer::Board_marginRatio_x * SCR_WIDTH) - (fragmentSize * board.width)/2;
    int UI_margin_y = floor(SpriteRenderer::Board_marginRatio_y * SCR_HEIGHT) - (fragmentSize * board.height)/2;
    
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
    
    float scaleY;
    float scaleX;
    
    float screenAspectRatio  = (float) SCR_WIDTH / (float) SCR_HEIGHT;
    float textureAspectRatio = (float) SpriteRenderer::textures[texIndex].width / (float) SpriteRenderer::textures[texIndex].height;
    
    if(screenAspectRatio <= textureAspectRatio){
        scaleY = SCR_HEIGHT;
        scaleX = textureAspectRatio * SCR_HEIGHT;
    }else{
        scaleX = SCR_WIDTH;
        scaleY = (1/textureAspectRatio) * SCR_WIDTH;
    }
    
    model = glm::scale(model, glm::vec3(scaleX, scaleY, 1.0f));
    
    SpriteRenderer::backgroundShader->use();
    SpriteRenderer::backgroundShader->setMat4("projection", glm::ortho(0.0f, (float) SCR_WIDTH, (float) SCR_HEIGHT, 0.0f, -1.0f, 1.0f));
    SpriteRenderer::backgroundShader->setMat4("model", model);
    
    SpriteRenderer::backgroundShader->setInt("backgroundTexture", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, SpriteRenderer::textures[texIndex].ID);
    
    glBindVertexArray(SpriteRenderer::VAO);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
}

void SpriteRenderer::renderTetromino(unsigned int texIndex, Tetromino* tetromino, GameBoard board, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    SpriteRenderer::fragmentShader->use();
    SpriteRenderer::fragmentShader->setInt("fragmentTexture", 0);
    SpriteRenderer::fragmentShader->setMat4("projection", glm::ortho(0.0f, (float) SCR_WIDTH, (float) SCR_HEIGHT, 0.0f, -1.0f, 1.0f));
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, SpriteRenderer::textures[texIndex].ID);
    
    glBindVertexArray(SpriteRenderer::VAO);
    
    int fragmentSize = floor(SpriteRenderer::fragmentSizeRatio * SCR_HEIGHT);
    
    int UI_margin_x = floor(SpriteRenderer::Board_marginRatio_x * SCR_WIDTH) - (fragmentSize * board.width)/2;
    int UI_margin_y = floor(SpriteRenderer::Board_marginRatio_y * SCR_HEIGHT) - (fragmentSize * board.height)/2;
    
    for(unsigned int i = 0; i < tetromino->rotations[tetromino->a_rot].fragments.size(); i++){
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(UI_margin_x + (tetromino->rotations[tetromino->a_rot].fragments[i].p_x + tetromino->posX) * fragmentSize, UI_margin_y + (board.height - (tetromino->rotations[tetromino->a_rot].fragments[i].p_y + tetromino->posY)) * fragmentSize, 0));
        model = glm::scale(model, glm::vec3(fragmentSize));
        
        SpriteRenderer::renderFragment(tetromino->rotations[tetromino->a_rot].fragments[i], model);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

void SpriteRenderer::renderUI(unsigned int scoreIndex, unsigned int frameIndex, unsigned int score, GameBoard gameBoard, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    SpriteRenderer::renderFrame(frameIndex, gameBoard, SCR_WIDTH, SCR_HEIGHT);
    SpriteRenderer::renderScore(scoreIndex, score, gameBoard, SCR_WIDTH, SCR_HEIGHT);
}
