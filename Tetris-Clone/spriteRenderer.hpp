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

class SpriteRenderer{
private:
    unsigned int VAO, VBO;
    std::vector<unsigned int> textures;
    
    Shader fragmentShader;
    Shader backgroundShader;
    
    float UI_marginRatio_x = 1.0f/2.0f, UI_marginRatio_y = 1.0f/2.0f;
    float fragmentSizeRatio = 1.0f/25.0f;
    
    void renderFragment(Fragment fragment, glm::mat4 model);
public:
    SpriteRenderer();
    
    int loadTexture(std::string path);
    
    void renderBoard(unsigned int texIndex, GameBoard board, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    void renderTetromino(unsigned int texIndex, Tetromino* tetromino, GameBoard board, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    void renderBackground(unsigned int texIndex,  unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
};

#endif /* spriteRenderer_hpp */
