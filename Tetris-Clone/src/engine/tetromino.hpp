//
//  tetromino.hpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 27/02/2021.
//

#ifndef tetromino_hpp
#define tetromino_hpp

#include <iostream>
#include <random>
#include <vector>

#include "fragment.hpp"

enum Shapes{
    I_PIECE,
    O_PIECE,
    T_PIECE,
    S_PIECE,
    Z_PIECE,
    J_PIECE,
    L_PIECE,
};

enum directions{
    DIR_DOWN,
    DIR_RIGHT,
    DIR_LEFT
};

enum rotations{
    ROT_NORTH,
    ROT_EAST,
    ROT_SOUTH,
    ROT_WEST
};

struct GameBoard{
    int width;
    int height;
    
    std::vector<std::vector<Fragment> > layout;
};

struct Rotation{
    int width = 0;
    int height = 0;
    std::vector<Fragment> fragments;
};

class Tetromino{
private:
    int shape;
public:
    int posX, posY;
    int a_rot;
    
    std::vector<Rotation> rotations;
    
    Tetromino(int pos_x, int pos_y);
    
    void draw();
    void move(int direction, GameBoard board);
    void rotate(int rot, GameBoard board);
    bool checkCollision(GameBoard &board, bool &gameOver);
};

#endif /* tetromino_hpp */
