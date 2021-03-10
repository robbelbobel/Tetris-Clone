//
//  fragment.hpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 27/02/2021.
//

#ifndef fragment_hpp
#define fragment_hpp

#include <stdio.h>
#include <vector>

enum Colors{
    AQUA,
    YELLOW,
    PURPLE,
    GREEN,
    RED,
    PINK,
    ORANGE,
    WHITE
};

class Fragment{
public:
    bool isEmpty;
    
    int p_x, p_y;
    unsigned int color;
    
    Fragment(unsigned int posX, unsigned int posY, int fragColor);
    Fragment();
    void draw();
};

#endif /* fragment_hpp */
