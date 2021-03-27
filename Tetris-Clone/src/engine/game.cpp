//
//  game.cpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 27/02/2021.
//

#include "game.hpp"

void Game::moveHandler(unsigned int button){
    bool canMove = false;
    
    if(Game::moveCounter > (1.0f / Game::moveSpeed)){
        canMove = true;
        Game::moveCounter = 0;
    }
    
    if(canMove){
        switch(button){
            case BUTTON_RIGHT:
                Game::activeTetromino->move(DIR_RIGHT, Game::gameBoard);
                break;
                
            case BUTTON_LEFT:
                Game::activeTetromino->move(DIR_LEFT, Game::gameBoard);
                break;
                
            case BUTTON_DOWN:
                Game::activeTetromino->move(DIR_DOWN, Game::gameBoard);
                break;
        }
    }
}

void Game::rotationHandler(unsigned int button){
    if(button == BUTTON_ROTATE){
        if(Game::canRotate){
            unsigned int newRotation;
            
            if(Game::activeTetromino->a_rot < 3){
                newRotation = Game::activeTetromino->a_rot + 1;
            }else{
                newRotation = ROT_NORTH;
            }
            
            Game::activeTetromino->rotate(newRotation, Game::gameBoard);
            Game::canRotate = false;
        }
    }else{
        Game::canRotate = true;
    }
}

void Game::render(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    Game::gameDisplayManager->render(Game::gameBoard, Game::activeTetromino, Game::score, SCR_WIDTH, SCR_HEIGHT);
}

void Game::fall(float deltaTime){
    // Update counter
    Game::fallCounter -= deltaTime;
    
    if(Game::fallCounter <= 0){
        Game::activeTetromino->move(DIR_DOWN, gameBoard);
        Game::fallCounter = Game::fallSpeed;
    }
}

void Game::checkRows(){
    std::vector<int> clearedLines = {};
    for(unsigned int y = 0; y < Game::gameBoard.height; y++){
        int rowFragments = 0;
        for(unsigned int x = 0; x < Game::gameBoard.width; x++){
            if(!Game::gameBoard.layout[y][x].isEmpty){
                rowFragments++;
            }
        }
        if(rowFragments == Game::gameBoard.width){
            clearedLines.push_back(y);
        }
    }
    
    if(clearedLines.size() > 0){
        // Update gameboard
        for(unsigned int i = clearedLines[0]; i < Game::gameBoard.layout.size(); i++){
            if(i + clearedLines.size() < (Game::gameBoard.height - 1)){
                Game::gameBoard.layout[i] = Game::gameBoard.layout[i + clearedLines.size()];
            }else{
                Game::gameBoard.layout[i] = std::vector<Fragment>(Game::gameBoard.width, Fragment());
            }
        }
        
        // Update score
        switch(clearedLines.size()){
            case 1:
                Game::score += 100;
                break;
            case 2:
                Game::score += 300;
                break;
            case 3:
                Game::score += 500;
                break;
            case 4:
                Game::score += 800;
                break;
            default:
                break;
        }
    }
}

Game::Game(GLFWwindow* win, SpriteRenderer* spriteRenderer, ResourceManager* resourceManager){
    Game::gameBoard.width = 10;
    Game::gameBoard.height = 20;
    Game::spriteRenderer = spriteRenderer;
    Game::resourceManager = resourceManager;
    Game::gameDisplayManager = new GameDisplayManager(Game::resourceManager, Game::spriteRenderer);
    
    // Initialize the board layout with empty fragments
    for(unsigned int i = 0; i < Game::gameBoard.height; i++){
        Game::gameBoard.layout.push_back(std::vector<Fragment>(Game::gameBoard.width, Fragment()));
    }
    
    // Initialize class variables
    Game::window = win;
    Game::score = 0.0f;
    Game::activeTetromino = new Tetromino(floor(Game::gameBoard.width/2), Game::gameBoard.height);
}

void Game::update(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT, float deltaTime){
    // Check if the active tetromino has collided
    if(Game::activeTetromino->checkCollision(Game::gameBoard, Game::gameOver)){
        // Delete the old tetromino
        delete Game::activeTetromino;
        Game::activeTetromino = nullptr;
        
        // Check if a line has been cleared
        Game::checkRows();
        Game::activeTetromino = new Tetromino(floor(Game::gameBoard.width/2), Game::gameBoard.height);
    }
    
    // Draw the game
    Game::render(SCR_WIDTH, SCR_HEIGHT);
    
    // Update Variables
    Game::moveCounter += deltaTime;
    
    // Make the active tetromino fall
    Game::fall(deltaTime);
}
