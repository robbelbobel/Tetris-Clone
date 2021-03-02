//
//  fragment.cpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 27/02/2021.
//

#include "fragment.hpp"

Fragment::Fragment(unsigned int posX, unsigned int posY, int fragColor){
    Fragment::isEmpty = false;
    Fragment::p_x = posX;
    Fragment::p_y = posY;
    Fragment::color = fragColor;
}

Fragment::Fragment(){
    Fragment::isEmpty = true;
    Fragment::color = WHITE;
}

void Fragment::draw(){
    if(Fragment::isEmpty){
        return;
    }
    //DRAW HERE
}
