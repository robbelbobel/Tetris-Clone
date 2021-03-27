//
//  displayManager.hpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 16/03/2021.
//

#ifndef displayManager_hpp
#define displayManager_hpp

#include <stdio.h>
#include "spriteRenderer.hpp"
#include "resourceManager.hpp"
#include <string>
#include <vector>

// Parent Class
class DisplayManager{
protected:
    SpriteRenderer* spriteRenderer;
    
    ResourceManager* resourceManager;
    
public:
    DisplayManager(ResourceManager* resourceManager, SpriteRenderer* spriteRenderer);
};

//-----Inherited Classes-----
// Game Display Manager Class
class GameDisplayManager : public DisplayManager{
private:
    //-----PRIVATE RENDER FUNCTIONS-----
    // UI Render Functions
    void renderUI(unsigned int score, GameBoard gameBoard, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    void renderBoardFrame(GameBoard gameBoard, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    void renderScore(unsigned int score, GameBoard gameBoard, unsigned SCR_WIDTH, unsigned int SCR_HEIGHT);
    void renderBackground(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    // Board Render Functions
    void renderTetromino(Tetromino* tetromino, GameBoard gameBoard, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    void renderBoard(GameBoard gameBoard, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    
    //-----PRIVATE VARIABLES-----
    const int totalFrameHeightMargin = 8;
    const int totalFrameWidthMarginLeft = 42, totalFrameWidthMarginRight = 4;
    
    const float Board_marginRatio_x = 1.0f / 2.0f, Board_marginRatio_y = 1.0f / 2.0f;
    const float fragmentSizeRatio = 1.0f / 25.0f;
    const float scoreHeightRatio = 1.0f / 20.0f, score_marginRatio_x = 1.0f / 2.0f;
    const float scoreClearanceY = 1.0f /15.0f, numClearanceX = 1.0f / 4.0f;
    
public:
    using DisplayManager::DisplayManager;
    void render(GameBoard gameBoard, Tetromino* tetromino, unsigned int score, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
};

// Menu Display Manager Class
class MenuDisplayManager : public DisplayManager{
private:
    void renderButtons(std::vector<Button*> buttons, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    void renderBackground(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
public:
    using DisplayManager::DisplayManager;
    void render(std::vector<Button*> buttons, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
};

#endif /* displayManager_hpp */
