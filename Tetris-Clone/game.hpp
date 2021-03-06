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
    
    // Time Variables
    float fallSpeed = 0.5f;
    float counter = 0.0f;
    float d_time = 0.0f;
    float old_time;
    
    unsigned int fragTex;
    unsigned int backgroundTex;
    
    unsigned int score;
    
    bool gameOver;
    bool inputListening = true;
    
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
