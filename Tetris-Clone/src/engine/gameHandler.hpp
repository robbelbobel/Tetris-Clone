//
//  gameHandler.hpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 15/03/2021.
//

#ifndef gameHandler_hpp
#define gameHandler_hpp

#include <stdio.h>
#include <string>

#include "resourceManager.hpp"
#include "menu.hpp"
#include "game.hpp"

enum gameStates{
    GAME_MENU,
    GAME_PAUSE,
    GAME_RUNNING
};

class GameHandler{
private:
    std::string assetPath = "/Users/robbetiteca/projects/Tetris-Clone/Tetris-Clone/src/game/assets/";
    std::string shaderPath = "/Users/robbetiteca/projects/Tetris-Clone/Tetris-Clone/src/engine/shaders/";
    
    ResourceManager* resourceManager;
    
    GLFWwindow* win;
    
    SpriteRenderer* spriteRenderer;
    
    unsigned int gameState;
    
    Game* game;
    Menu* menu;
    
    void inputHandler(float SCR_WIDTH, float SCR_HEIGHT);
    void updateTime();
    
    // Time Variables
    float deltaTime = 0.0f, oldTime = 0.0f;
    
public:
    GameHandler(GLFWwindow* win);
    void update(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
};


#endif /* gameHandler_hpp */
