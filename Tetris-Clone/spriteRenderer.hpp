//
//  spriteRenderer.hpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 28/02/2021.
//

#ifndef spriteRenderer_hpp
#define spriteRenderer_hpp

#include "shader.hpp"
#include <string>
#include <vector>
#include "include/stb_image.h"

#include "tetromino.hpp"

struct Texture{
    unsigned int ID;
    unsigned int width;
    unsigned int height;
    unsigned int nrChannels;
};

class SpriteRenderer{
private:
    unsigned int VAO, VBO;
    std::vector<Texture> textures;
    std::vector<unsigned int> numTextures;
    
    Shader *fragmentShader;
    Shader *backgroundShader;
    Shader *genericShader;
    
    float Board_marginRatio_x = 1.0f / 2.0f, Board_marginRatio_y = 1.0f / 2.0f;
    float fragmentSizeRatio = 1.0f / 25.0f;
    float score_marginRatio_y = 1.0f / 3.0f, scoreWidthRatio = 1.0f / 7.0f;
    float scoreClearanceY = 1.0f / 4.0f, numClearanceX = 1.0f / 4.0f;
    
    void renderFragment(Fragment fragment, glm::mat4 model);
    void renderScore(unsigned int texIndex, unsigned int score, GameBoard gameBoard, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
public:
    SpriteRenderer();
    
    int loadTexture(std::string path);
    int loadNumbers(std::string path);
    
    void renderBoard(unsigned int texIndex, GameBoard board, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    void renderTetromino(unsigned int texIndex, Tetromino* tetromino, GameBoard board, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    void renderBackground(unsigned int texIndex,  unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    void renderUI(unsigned int texIndex, unsigned int score, GameBoard gameBoard, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
};

#endif /* spriteRenderer_hpp */
