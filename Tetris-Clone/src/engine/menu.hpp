//
//  menu.hpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 15/03/2021.
//

#ifndef menu_hpp
#define menu_hpp

#include <stdio.h>
#include <iostream>
#include "resourceManager.hpp"
#include "spriteRenderer.hpp"
#include "displayManager.hpp"
#include "button.hpp"

class Menu{
private:
    // Private Variables
    ResourceManager* resourceManager;
    SpriteRenderer* spriteRenderer;
    MenuDisplayManager* menuDisplayManager;
    
    std::vector<Button*> buttons;
    
    // Private Functions
    void render(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
    
public:
    Menu(SpriteRenderer* spriteRenderer, ResourceManager* resourceManager);
    
    // Public Functions
    void update(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT, unsigned int deltaTime);
    void mousePositionHandler(double xPos, double yPos, float SCR_WIDTH, float SCR_HEIGHT);
};

#endif /* menu_hpp */
