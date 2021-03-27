//
//  button.cpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 15/03/2021.
//

#include "button.hpp"

Button::Button(float posX, float posY, float width, Texture* texture, unsigned int function){
    Button::posX = posX;
    Button::posY = posY;
    
    Button::width = width;
    
    Button::texture = texture;
    
    Button::function = function;
}

bool Button::isClicked(double pointerX, double pointerY, float SCR_WIDTH, float SCR_HEIGHT){
//    if(pointerX > Button::posX && pointerX < Button::posX + width){
//        if(pointerY > Button::posY && pointerY < Button::posY + height){
//            return true;
//        }else{
//            return false;
//        }
//    }else{
//        return false;
//    }
    
    float buttonWidth = Button::width * SCR_WIDTH;
    float buttonHeight = ((Button::texture->height / (float) Button::texture->width) * Button::width * SCR_WIDTH);
    
    float buttonPosX = Button::posX * SCR_WIDTH;
    float buttonPosY = Button::posX * SCR_HEIGHT;
    
    // Return True If Pointer is in Button
    return(pointerX > Button::posX && pointerY < buttonPosX + buttonWidth && pointerY > buttonPosY && pointerY < buttonPosY + buttonHeight);
}

float Button::getWidth(float SCR_WIDTH){
    return (float) Button::width * SCR_WIDTH;
}

float Button::getHeight(float SCR_WIDTH){
    return ((float) Button::texture->height / (float) Button::texture->width) * Button::width * SCR_WIDTH;
}

float Button::getPosX(float SCR_WIDTH){
    return Button::posX * SCR_WIDTH;
}

float Button::getPosY(float SCR_HEIGHT){
    return (float) Button::posY * SCR_HEIGHT;
}
