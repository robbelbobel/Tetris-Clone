//
//  game.hpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 27/02/2021.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>
#include "spriteRenderer.hpp"
#include "resourceManager.hpp"
#include "displayManager.hpp"
#include <GLFW/glfw3.h>

enum buttons{
    BUTTON_RIGHT,
    BUTTON_LEFT,
    BUTTON_DOWN,
    BUTTON_ROTATE,
    BUTTON_NONE
};

class Game{
private:
    Tetromino *activeTetromino = nullptr;
    GameBoard gameBoard;
    
    GLFWwindow* window = nullptr;
    
    SpriteRenderer* spriteRenderer;
    ResourceManager* resourceManager;
    GameDisplayManager* gameDisplayManager;
    
    // -----Time Variables-----
    // Move Variables
    const unsigned int moveSpeed = 10;
    float moveCounter = 0.0f;
    bool canRotate;
    // Fall Variables
    const float fallSpeed = 0.5f;
    float fallCounter = 0.0f;
    
    // Texture ID's
    unsigned int fragTex;
    unsigned int backgroundTex;
    unsigned int frameTex;
    unsigned int scoreTex;
    
    unsigned int score;
    
    // Game State Variables
    bool gameOver;
    
    // Private Game Functions
    void render(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    void fall(float deltaTime);
    void checkRows();
    
public:
    void moveHandler(unsigned int button);
    void rotationHandler(unsigned int button);
    
    Game(GLFWwindow* win, SpriteRenderer* spriteRenderer, ResourceManager* resourceManager);
    void update(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT, float deltaTime);
};

#endif /* game_hpp */
