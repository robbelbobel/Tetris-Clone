//
//  gameHandler.cpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 15/03/2021.
//

#include "gameHandler.hpp"

GameHandler::GameHandler(GLFWwindow* win){
    // Assign class variables
    GameHandler::win = win;
    GameHandler::gameState = GAME_RUNNING;
    GameHandler::oldTime = (float) glfwGetTime();
    
    GameHandler::spriteRenderer = new SpriteRenderer;
    
    // Instantiate Instances
    GameHandler::resourceManager = new ResourceManager(GameHandler::spriteRenderer, GameHandler::assetPath, GameHandler::shaderPath);
    GameHandler::menu = new Menu(GameHandler::spriteRenderer, GameHandler::resourceManager);
    GameHandler::game = new Game(GameHandler::win, GameHandler::spriteRenderer, GameHandler::resourceManager);
}

void GameHandler::inputHandler(float SCR_WIDTH, float SCR_HEIGHT){
    if(glfwGetKey(GameHandler::win, GLFW_KEY_ESCAPE)){
        glfwSetWindowShouldClose(GameHandler::win, GLFW_TRUE);
    }
    
    unsigned int button;
    if(glfwGetKey(GameHandler::win, GLFW_KEY_RIGHT)){
        button = BUTTON_RIGHT;
    }else if(glfwGetKey(GameHandler::win, GLFW_KEY_LEFT)){
        button = BUTTON_LEFT;
    }else if(glfwGetKey(GameHandler::win, GLFW_KEY_DOWN)){
        button = BUTTON_DOWN;
    }else{
        button = BUTTON_NONE;
    }
    
    unsigned int rotationButton;
    if(glfwGetKey(GameHandler::win, GLFW_KEY_SPACE)){
        rotationButton = BUTTON_ROTATE;
    }else{
        rotationButton = BUTTON_NONE;
    }
    
    // Get Mouse Position
    double mouseX, mouseY;
    glfwGetCursorPos(GameHandler::win, &mouseX, &mouseY);
    
    switch(GameHandler::gameState){
        case GAME_MENU:
            GameHandler::menu->mousePositionHandler(mouseX, mouseY, SCR_WIDTH, SCR_HEIGHT);
            break;
        case GAME_RUNNING:
            GameHandler::game->moveHandler(button);
            GameHandler::game->rotationHandler(rotationButton);
            break;
        default:
            break;
    }
}

void GameHandler::updateTime(){
    // Calculate the time passed every frame
    GameHandler::deltaTime = (float) glfwGetTime() - GameHandler::oldTime;
    GameHandler::oldTime = (float) glfwGetTime();
}

void GameHandler::update(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    switch(GameHandler::gameState){
        case GAME_RUNNING:
            GameHandler::game->update(SCR_WIDTH, SCR_HEIGHT, GameHandler::deltaTime);
            break;
        case GAME_MENU:
            GameHandler::menu->update(SCR_WIDTH, SCR_HEIGHT, GameHandler::deltaTime);
    }
    
    // Get input
    GameHandler::inputHandler(SCR_WIDTH, SCR_HEIGHT);
    
    //-----UPDATE VARIABLES-----
    // Update time variables
    GameHandler::updateTime();
}
