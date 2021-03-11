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
#include <GLFW/glfw3.h>

enum gameStates{
    GAME_MENU,
    GAME_PAUSE,
    GAME_RUNNING
};

class Game{
private:
    Tetromino *activeTetromino = nullptr;
    GameBoard gameBoard;
    
    SpriteRenderer spriteRenderer;
    
    GLFWwindow* window = nullptr;
    
    // -----Time Variables-----
    // Move Variables
    const unsigned int moveSpeed = 10;
    float moveCounter = 0.0f;
    // Fall Variables
    const float fallSpeed = 0.5f;
    float fallCounter = 0.0f;
    // Delta Time Variables
    float d_time = 0.0f;
    float old_time;
    
    unsigned int fragTex;
    unsigned int backgroundTex;
    unsigned int frameTex;
    unsigned int scoreTex;
    
    unsigned int score;
    
    bool gameOver;
    bool canRotate;
    
    void inputHandler();
    void render(unsigned int scr_width, unsigned int scr_height);
    void fall();
    void checkRows();
    
    int activeGameState;
    
public:
    Game(GLFWwindow* win);
    //Main update function
    void update(unsigned int scr_width, unsigned int scr_height);
};

#endif /* game_hpp */
