//
//  menu.cpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 15/03/2021.
//

#include "menu.hpp"

Menu::Menu(SpriteRenderer* spriteRenderer, ResourceManager* resourceManager){
    Menu::spriteRenderer = spriteRenderer;
    Menu::resourceManager = resourceManager;
    Menu::menuDisplayManager = new MenuDisplayManager(Menu::resourceManager, Menu::spriteRenderer);
    
    // Create Buttons
    Menu::buttons.push_back(new Button(-0.5f, 0.0f, 0.25f, Menu::resourceManager->playButtonTexture, BUTTON_FUNC_PLAY));
}

void Menu::render(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){
    Menu::menuDisplayManager->render(Menu::buttons, SCR_WIDTH, SCR_HEIGHT);
}

void Menu::update(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT, unsigned int deltaTime){
    Menu::render(SCR_WIDTH, SCR_HEIGHT);
}

void Menu::mousePositionHandler(double xPos, double yPos, float SCR_WIDTH, float SCR_HEIGHT){
    for(unsigned int i = 0; i < Menu::buttons.size(); i++){
        if(Menu::buttons[i]->isClicked(xPos, yPos, SCR_WIDTH, SCR_HEIGHT)){
            break;
        }
    }
}
