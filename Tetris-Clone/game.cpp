//
//  game.cpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 27/02/2021.
//

#include "game.hpp"

void Game::inputHandler(){
    if(glfwGetKey(Game::window, GLFW_KEY_ESCAPE)){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        
    }
    if(glfwGetKey(Game::window, GLFW_KEY_RIGHT)){
        if(Game::inputListening){
            Game::activeTetromino->move(DIR_RIGHT, Game::gameBoard);
            Game::inputListening = false;
        }
    }else if(glfwGetKey(Game::window, GLFW_KEY_LEFT)){
        if(Game::inputListening){
            Game::activeTetromino->move(DIR_LEFT, Game::gameBoard);
            Game::inputListening = false;
        }
    }else if(glfwGetKey(Game::window, GLFW_KEY_DOWN)){
        if(Game::inputListening){
            Game::activeTetromino->move(DIR_DOWN, Game::gameBoard);
            Game::inputListening = false;
        }
    }else if(glfwGetKey(Game::window, GLFW_KEY_SPACE)){
        if(Game::inputListening){
            int rot;
            if(Game::activeTetromino->a_rot < 3){
                rot = Game::activeTetromino->a_rot + 1;
            }else{
                rot = ROT_NORTH;
            }
            
            Game::activeTetromino->rotate(rot, Game::gameBoard);
            
            Game::inputListening = false;
        }
    }else{
        Game::inputListening = true;
    }
}

void Game::render(unsigned int scr_width, unsigned int scr_height){
    // Draw the background
    Game::spriteRenderer.renderBackground(Game::backgroundTex, scr_width, scr_height);
    // Draw the gameboard
    Game::spriteRenderer.renderBoard(Game::fragTex, Game::gameBoard, scr_width, scr_height);
    // Draw the falling tetromino
    Game::spriteRenderer.renderTetromino(Game::fragTex, Game::activeTetromino, Game::gameBoard, scr_width, scr_height);
}

void Game::fall(){
    // Update deltatime
    Game::d_time = (float) glfwGetTime() - Game::old_time;
    Game::old_time = (float) glfwGetTime();
    
    // Update counter
    Game::counter -= d_time;
    
    if(Game::counter <= 0){
        Game::activeTetromino->move(DIR_DOWN, gameBoard);
        Game::counter = Game::fallSpeed;
    }
}

Game::Game(GLFWwindow* win){
    Game::gameBoard.width = 10;
    Game::gameBoard.height = 20;
    
    // Initialize the board layout with empty fragments
    for(unsigned int i = 0; i < Game::gameBoard.height; i++){
        Game::gameBoard.layout.push_back(std::vector<Fragment>(Game::gameBoard.width, Fragment()));
    }
    
    Game::window = win;
    Game::old_time = (float) glfwGetTime();
    
    Game::fragTex = Game::spriteRenderer.loadTexture("/Users/robbetiteca/projects/Tetris-Clone/Tetris-Clone/assets/fragment.png");
    Game::backgroundTex = Game::spriteRenderer.loadTexture("/Users/robbetiteca/projects/Tetris-Clone/Tetris-Clone/assets/background.png");
}

void Game::update(unsigned int scr_width, unsigned int scr_height){
    // Check if there is a falling tetromino, if there isn't make one.
    if(Game::activeTetromino == nullptr){
        Game::activeTetromino = new Tetromino(floor(Game::gameBoard.width/2), Game::gameBoard.height);
    }
    
    // Draw the game
    Game::render(scr_width, scr_height);
    
    // Check Input
    Game::inputHandler();
    
    // Make the active tetromino fall
    Game::fall();
    
    // Check if the tetromino has collided with a fragment
    if(Game::activeTetromino -> checkCollision(Game::gameBoard, Game::gameOver)){
        delete Game::activeTetromino;
        Game::activeTetromino = nullptr;
    }
}