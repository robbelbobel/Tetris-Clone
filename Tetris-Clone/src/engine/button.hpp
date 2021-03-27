//
//  button.hpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 15/03/2021.
//

#ifndef button_hpp
#define button_hpp

#include <stdio.h>
#include "spriteRenderer.hpp"

// Forward Declaration of Texture
struct Texture;

enum ButtonFunctions{
    BUTTON_FUNC_PLAY,
    BUTTON_FUNC_SETTINGS,
    BUTTON_FUNC_QUIT
};

class Button{
    float width, height;
    unsigned int posX, posY;
public:
    Button(float posX, float posY, float width, Texture* texture, unsigned int function);
    
    // Public Functions
    bool isClicked(double pointerX, double pointerY, float SCR_WIDTH, float SCR_HEIGHT);
    
    float getWidth(float SCR_WIDTH);
    float getHeight(float SCR_WIDTH);
    float getPosX(float SCR_WIDTH);
    float getPosY(float SCR_HEIGHT);
    
    // Public Variables
    unsigned int function;
    
    Texture* texture;
};

#endif /* button_hpp */
