//
//  tetromino.cpp
//  Tetris-Clone
//
//  Created by Robbe Titeca on 27/02/2021.
//

#include "tetromino.hpp"

Tetromino::Tetromino(int pos_x, int pos_y){
    Tetromino::shape = (int) rand() % 7;
    Tetromino::a_rot = ROT_NORTH;
    
    switch(shape){
        case I_PIECE: {
            //-----PRECALCULATED ROTATIONS-----
            //Northern(standard) Rotation
            Rotation n_rot;
            
            n_rot.fragments.push_back(Fragment(0, 0, AQUA));
            n_rot.fragments.push_back(Fragment(1, 0, AQUA));
            n_rot.fragments.push_back(Fragment(2, 0, AQUA));
            n_rot.fragments.push_back(Fragment(3, 0, AQUA));
            n_rot.height = 1;
            n_rot.width = 4;
            
            //Eastern Rotation
            Rotation e_rot;
            e_rot.fragments.push_back(Fragment(0, 0, AQUA));
            e_rot.fragments.push_back(Fragment(0, 1, AQUA));
            e_rot.fragments.push_back(Fragment(0, 2, AQUA));
            e_rot.fragments.push_back(Fragment(0, 3, AQUA));
            e_rot.height = 4;
            e_rot.width = 1;
            
            //Southern Rotation
            Rotation s_rot;
            s_rot.fragments.push_back(Fragment(0, 0, AQUA));
            s_rot.fragments.push_back(Fragment(1, 0, AQUA));
            s_rot.fragments.push_back(Fragment(2, 0, AQUA));
            s_rot.fragments.push_back(Fragment(3, 0, AQUA));
            s_rot.height = 1;
            s_rot.width = 4;
            
            //Western Rotation
            Rotation w_rot;
            w_rot.fragments.push_back(Fragment(0, 0, AQUA));
            w_rot.fragments.push_back(Fragment(0, 1, AQUA));
            w_rot.fragments.push_back(Fragment(0, 2, AQUA));
            w_rot.fragments.push_back(Fragment(0, 3, AQUA));
            w_rot.height = 4;
            w_rot.width = 1;
            
            Tetromino::rotations.push_back(n_rot);
            Tetromino::rotations.push_back(e_rot);
            Tetromino::rotations.push_back(s_rot);
            Tetromino::rotations.push_back(w_rot);
            
            break;
        }
            
        case O_PIECE:{
            //-----PRECALCULATED ROTATIONS-----
            //Northern(standard) Rotation
            Rotation n_rot;
            n_rot.fragments.push_back(Fragment(0, 0, YELLOW));
            n_rot.fragments.push_back(Fragment(1, 0, YELLOW));
            n_rot.fragments.push_back(Fragment(0, 1, YELLOW));
            n_rot.fragments.push_back(Fragment(1, 1, YELLOW));
            n_rot.height = 2;
            n_rot.width = 2;;
            
            //Eastern Rotation
            Rotation e_rot;
            e_rot.fragments.push_back(Fragment(0, 0, YELLOW));
            e_rot.fragments.push_back(Fragment(1, 0, YELLOW));
            e_rot.fragments.push_back(Fragment(0, 1, YELLOW));
            e_rot.fragments.push_back(Fragment(1, 1, YELLOW));
            e_rot.height = 2;
            e_rot.width = 2;;
            
            //Southern Rotation
            Rotation s_rot;
            e_rot.fragments.push_back(Fragment(0, 0, YELLOW));
            e_rot.fragments.push_back(Fragment(1, 0, YELLOW));
            e_rot.fragments.push_back(Fragment(0, 1, YELLOW));
            e_rot.fragments.push_back(Fragment(1, 1, YELLOW));
            s_rot.height = 2;
            s_rot.width = 2;;
            
            //Western Rotation
            Rotation w_rot;
            e_rot.fragments.push_back(Fragment(0, 0, YELLOW));
            e_rot.fragments.push_back(Fragment(1, 0, YELLOW));
            e_rot.fragments.push_back(Fragment(0, 1, YELLOW));
            e_rot.fragments.push_back(Fragment(1, 1, YELLOW));
            w_rot.height = 2;
            w_rot.width = 2;;
            
            Tetromino::rotations.push_back(n_rot);
            Tetromino::rotations.push_back(e_rot);
            Tetromino::rotations.push_back(s_rot);
            Tetromino::rotations.push_back(w_rot);
            
            break;
        }
            
        case T_PIECE:{
            //-----PRECALCULATED ROTATIONS-----
            //Northern(standard) Rotation
            Rotation n_rot;
            n_rot.fragments.push_back(Fragment(0, 0, PURPLE));
            n_rot.fragments.push_back(Fragment(1, 0, PURPLE));
            n_rot.fragments.push_back(Fragment(2, 0, PURPLE));
            n_rot.fragments.push_back(Fragment(1, 1, PURPLE));
            n_rot.height = 2;
            n_rot.width = 3;
            
            //Eastern Rotation
            Rotation e_rot;
            e_rot.fragments.push_back(Fragment(1, 0, PURPLE));
            e_rot.fragments.push_back(Fragment(0, 1, PURPLE));
            e_rot.fragments.push_back(Fragment(1, 1, PURPLE));
            e_rot.fragments.push_back(Fragment(1, 2, PURPLE));
            e_rot.height = 3;
            e_rot.width = 2;
            
            //Southern Rotation
            Rotation s_rot;
            s_rot.fragments.push_back(Fragment(1, 0, PURPLE));
            s_rot.fragments.push_back(Fragment(0, 1, PURPLE));
            s_rot.fragments.push_back(Fragment(1, 1, PURPLE));
            s_rot.fragments.push_back(Fragment(2, 1, PURPLE));
            s_rot.height = 2;
            s_rot.width = 3;
            
            //Western Rotation
            Rotation w_rot;
            w_rot.fragments.push_back(Fragment(0, 0, PURPLE));
            w_rot.fragments.push_back(Fragment(0, 1, PURPLE));
            w_rot.fragments.push_back(Fragment(1, 1, PURPLE));
            w_rot.fragments.push_back(Fragment(0, 2, PURPLE));
            w_rot.height = 3;
            w_rot.width = 2;
            
            Tetromino::rotations.push_back(n_rot);
            Tetromino::rotations.push_back(e_rot);
            Tetromino::rotations.push_back(s_rot);
            Tetromino::rotations.push_back(w_rot);
            
            break;
        }
            
        case S_PIECE:{
            //-----PRECALCULATED ROTATIONS-----
            //Northern(standard) Rotation
            Rotation n_rot;
            n_rot.fragments.push_back(Fragment(1, 0, GREEN));
            n_rot.fragments.push_back(Fragment(2, 0, GREEN));
            n_rot.fragments.push_back(Fragment(0, 1, GREEN));
            n_rot.fragments.push_back(Fragment(1, 1, GREEN));
            n_rot.height = 2;
            n_rot.width = 3;
            
            //Eastern Rotation
            Rotation e_rot;
            e_rot.fragments.push_back(Fragment(0, 0, GREEN));
            e_rot.fragments.push_back(Fragment(0, 1, GREEN));
            e_rot.fragments.push_back(Fragment(1, 1, GREEN));
            e_rot.fragments.push_back(Fragment(1, 2, GREEN));
            e_rot.height = 3;
            e_rot.width = 2;
            
            //Southern Rotation
            Rotation s_rot;
            s_rot.fragments.push_back(Fragment(1, 0, GREEN));
            s_rot.fragments.push_back(Fragment(2, 0, GREEN));
            s_rot.fragments.push_back(Fragment(0, 1, GREEN));
            s_rot.fragments.push_back(Fragment(1, 1, GREEN));
            s_rot.height = 2;
            s_rot.width = 3;
            
            //Western Rotation
            Rotation w_rot;
            w_rot.fragments.push_back(Fragment(0, 0, GREEN));
            w_rot.fragments.push_back(Fragment(0, 1, GREEN));
            w_rot.fragments.push_back(Fragment(1, 1, GREEN));
            w_rot.fragments.push_back(Fragment(1, 2, GREEN));
            w_rot.height = 3;
            w_rot.width = 2;
            
            Tetromino::rotations.push_back(n_rot);
            Tetromino::rotations.push_back(e_rot);
            Tetromino::rotations.push_back(s_rot);
            Tetromino::rotations.push_back(w_rot);
            
            break;
        }
            
        case Z_PIECE:{
            //-----PRECALCULATED ROTATIONS-----
            //Northern(standard) Rotation
            Rotation n_rot;
            n_rot.fragments.push_back(Fragment(0, 0, RED));
            n_rot.fragments.push_back(Fragment(1, 0, RED));
            n_rot.fragments.push_back(Fragment(1, 1, RED));
            n_rot.fragments.push_back(Fragment(2, 1, RED));
            n_rot.height = 2;
            n_rot.width = 3;
            
            //Eastern Rotation
            Rotation e_rot;
            e_rot.fragments.push_back(Fragment(1, 0, RED));
            e_rot.fragments.push_back(Fragment(0, 1, RED));
            e_rot.fragments.push_back(Fragment(1, 1, RED));
            e_rot.fragments.push_back(Fragment(0, 2, RED));
            e_rot.height = 3;
            e_rot.width = 2;
            
            //Southern Rotation
            Rotation s_rot;
            s_rot.fragments.push_back(Fragment(0, 0, RED));
            s_rot.fragments.push_back(Fragment(1, 0, RED));
            s_rot.fragments.push_back(Fragment(1, 1, RED));
            s_rot.fragments.push_back(Fragment(2, 1, RED));
            s_rot.height = 2;
            s_rot.width = 3;
            
            //Western Rotation
            Rotation w_rot;
            w_rot.fragments.push_back(Fragment(1, 0, RED));
            w_rot.fragments.push_back(Fragment(0, 1, RED));
            w_rot.fragments.push_back(Fragment(1, 1, RED));
            w_rot.fragments.push_back(Fragment(0, 2, RED));
            w_rot.height = 3;
            w_rot.width = 2;
            
            Tetromino::rotations.push_back(n_rot);
            Tetromino::rotations.push_back(e_rot);
            Tetromino::rotations.push_back(s_rot);
            Tetromino::rotations.push_back(w_rot);
            
            break;
        }
            
        case J_PIECE:{
            //-----PRECALCULATED ROTATIONS-----
            // Northern(standard) Rotation
            Rotation n_rot;
            n_rot.fragments.push_back(Fragment(1, 0, BLUE));
            n_rot.fragments.push_back(Fragment(1, 1, BLUE));
            n_rot.fragments.push_back(Fragment(0, 2, BLUE));
            n_rot.fragments.push_back(Fragment(1, 2, BLUE));
            n_rot.height = 3;
            n_rot.width = 2;
            
            // Eastern Rotation
            Rotation e_rot;
            e_rot.fragments.push_back(Fragment(0, 0, BLUE));
            e_rot.fragments.push_back(Fragment(0, 1, BLUE));
            e_rot.fragments.push_back(Fragment(1, 1, BLUE));
            e_rot.fragments.push_back(Fragment(2, 1, BLUE));
            e_rot.height = 2;
            e_rot.width = 3;
            
            // Southern Rotation
            Rotation s_rot;
            s_rot.fragments.push_back(Fragment(0, 0, BLUE));
            s_rot.fragments.push_back(Fragment(1, 0, BLUE));
            s_rot.fragments.push_back(Fragment(0, 1, BLUE));
            s_rot.fragments.push_back(Fragment(0, 2, BLUE));
            s_rot.height = 3;
            s_rot.width = 2;
            
            // Western Rotation
            Rotation w_rot;
            w_rot.fragments.push_back(Fragment(0, 0, BLUE));
            w_rot.fragments.push_back(Fragment(1, 0, BLUE));
            w_rot.fragments.push_back(Fragment(2, 0, BLUE));
            w_rot.fragments.push_back(Fragment(2, 1, BLUE));
            w_rot.height = 2;
            w_rot.width = 3;
            
            Tetromino::rotations.push_back(n_rot);
            Tetromino::rotations.push_back(e_rot);
            Tetromino::rotations.push_back(s_rot);
            Tetromino::rotations.push_back(w_rot);
            
            break;
        }
            
        case L_PIECE:{
            //-----PRECALCULATED ROTATIONS-----
            // Northern(standard) Rotation
            Rotation n_rot;
            n_rot.fragments.push_back(Fragment(0, 0, ORANGE));
            n_rot.fragments.push_back(Fragment(0, 1, ORANGE));
            n_rot.fragments.push_back(Fragment(0, 2, ORANGE));
            n_rot.fragments.push_back(Fragment(1, 2, ORANGE));
            n_rot.height = 3;
            n_rot.width = 2;
            
            // Eastern Rotation
            Rotation e_rot;
            e_rot.fragments.push_back(Fragment(0, 0, ORANGE));
            e_rot.fragments.push_back(Fragment(1, 0, ORANGE));
            e_rot.fragments.push_back(Fragment(2, 0, ORANGE));
            e_rot.fragments.push_back(Fragment(0, 1, ORANGE));
            e_rot.height = 2;
            e_rot.width = 3;
            
            // Southern Rotation
            Rotation s_rot;
            s_rot.fragments.push_back(Fragment(0, 0, ORANGE));
            s_rot.fragments.push_back(Fragment(1, 0, ORANGE));
            s_rot.fragments.push_back(Fragment(1, 1, ORANGE));
            s_rot.fragments.push_back(Fragment(1, 2, ORANGE));
            s_rot.height = 3;
            s_rot.width = 2;
            
            // Western Rotation
            Rotation w_rot;
            w_rot.fragments.push_back(Fragment(2, 0, ORANGE));
            w_rot.fragments.push_back(Fragment(0, 1, ORANGE));
            w_rot.fragments.push_back(Fragment(1, 1, ORANGE));
            w_rot.fragments.push_back(Fragment(2, 1, ORANGE));
            w_rot.height = 2;
            w_rot.width = 3;
            
            Tetromino::rotations.push_back(n_rot);
            Tetromino::rotations.push_back(e_rot);
            Tetromino::rotations.push_back(s_rot);
            Tetromino::rotations.push_back(w_rot);
            
            break;
        }
            
        default: {
            std::cout << "Error! Invalid shape: " << Tetromino::shape << "!" << std::endl;
        }
    }
    
    Tetromino::posX = pos_x - floor(Tetromino::rotations[Tetromino::a_rot].width / 2);
    Tetromino::posY = pos_y - Tetromino::rotations[Tetromino::a_rot].height;
}

void Tetromino::draw(){
    for(unsigned int i = 0; i < Tetromino::rotations[a_rot].fragments.size(); i++){
        Tetromino::rotations[Tetromino::a_rot].fragments[Tetromino::posX + i].draw();
    }
}

void Tetromino::move(int direction, GameBoard board){
    if(direction == DIR_DOWN){
        bool moveable = true;
        for (unsigned int i = 0; i < Tetromino::rotations[Tetromino::a_rot].fragments.size(); i++){
            if(!board.layout[Tetromino::posY + Tetromino::rotations[Tetromino::a_rot].fragments[i].p_y][Tetromino::posX + Tetromino::rotations[Tetromino::a_rot].fragments[i].p_x].isEmpty){
                moveable = false;
            }
        }
        
        if(moveable){
            Tetromino::posY -= 1;
        }
    }
    
    if(direction == DIR_LEFT){
        bool moveable = true;
        
        // Check If All Fragments Are Able to Move
        for(unsigned int i = 0; i < Tetromino::rotations[Tetromino::a_rot].fragments.size(); i++){
            // Check if the fragment is at the left and bottom edge of the gameboard
            if(Tetromino::rotations[Tetromino::a_rot].fragments[i].p_x + Tetromino::posX > 0 && Tetromino::rotations[Tetromino::a_rot].fragments[i].p_y + Tetromino::posY > 0){
                // Check if the Fragment left of the Fragment is empty
                if(!board.layout[Tetromino::rotations[Tetromino::a_rot].fragments[i].p_y + Tetromino::posY][Tetromino::rotations[Tetromino::a_rot].fragments[i].p_x + Tetromino::posX - 1].isEmpty){
                    moveable = false;
                }
            }else{
                moveable = false;
            }
        }
        
        // If All Fragments Are Able to Move, Move Them
        if(moveable){
            Tetromino::posX -= 1;
        }
    }
    
    if(direction == DIR_RIGHT){
        bool moveable = true;
        
        // Check If All Fragments Are Able to Move
        for(unsigned int i = 0; i < Tetromino::rotations[Tetromino::a_rot].fragments.size(); i++){
            // Check if the fragment is at the right and bottom edge of the gameboard
            if((Tetromino::rotations[Tetromino::a_rot].fragments[i].p_x + Tetromino::posX) < (board.width - 1) && (Tetromino::rotations[Tetromino::a_rot].fragments[i].p_y + Tetromino::posY) > 0){
                // Check if the Fragment right of the Fragment is empty
                if(!board.layout[Tetromino::rotations[Tetromino::a_rot].fragments[i].p_y + Tetromino::posY][Tetromino::rotations[Tetromino::a_rot].fragments[i].p_x + Tetromino::posX + 1].isEmpty){
                    moveable = false;
                }
            }else{
                moveable = false;
            }
        }
        
        // If All Fragments Are Able to Move, Move All Fragments
        if(moveable){
            Tetromino::posX += 1;
        }
    }
}


void Tetromino::rotate(int rot, GameBoard board){
    bool rotateable = true;
    
    int widthChange = Tetromino::rotations[rot].width - Tetromino::rotations[Tetromino::a_rot].width;
    int heightChange = Tetromino::rotations[rot].height - Tetromino::rotations[Tetromino::a_rot].height;
    
    if(!(widthChange == 0 && heightChange == 0)){
        for(unsigned int i = 0; i < Tetromino::rotations[rot].fragments.size(); i++){
            if(Tetromino::posX + Tetromino::rotations[rot].fragments[i].p_x >= 0 && Tetromino::posX + Tetromino::rotations[rot].fragments[i].p_x < board.width){
                if(Tetromino::posY + Tetromino::rotations[rot].fragments[i].p_y >= 0 && Tetromino::posY + Tetromino::rotations[rot].fragments[i].p_y < board.height){
                    if(!board.layout[Tetromino::posY + Tetromino::rotations[rot].fragments[i].p_y][Tetromino::posX + Tetromino::rotations[rot].fragments[i].p_x].isEmpty){
                        std::cout << "Can't rotate!" << std::endl;
                        rotateable = false;
                    }
                }else{
                    std::cout << "Can't rotate!" << std::endl;
                    rotateable =false;
                }
            }else{
                std::cout << "Can't rotate!" << std::endl;
                rotateable = false;
            }
        }
    }
    
    if(rotateable){
        Tetromino::a_rot = rot;
    }
    
}
    
    bool Tetromino::checkCollision(GameBoard &board, bool &gameOver){
        bool collided = false;
        // Check Collision For Every Fragment
        for(unsigned int i = 0; i < Tetromino::rotations[Tetromino::a_rot].fragments.size(); i++){
            // Check if fragment has reached the bottom
            if(Tetromino::rotations[Tetromino::a_rot].fragments[i].p_y + Tetromino::posY < 0){
                collided = true;
                break;
                // Check if fragment has collided with another fragment
            }else{
                if(!board.layout[Tetromino::rotations[Tetromino::a_rot].fragments[i].p_y + Tetromino::posY][Tetromino::rotations[Tetromino::a_rot].fragments[i].p_x + Tetromino::posX].isEmpty){
                    collided = true;
                    break;
                }
            }
        }
        
        // If a Fragment Has Collided With the Bottom of The Board It Gets Added to The GameBoard
        if(collided){
            for(unsigned int i = 0; i < Tetromino::rotations[Tetromino::a_rot].fragments.size(); i++){ //THIS IS STRANGE
                // Check If a Fragment is Higher Than The Maximum Height
                if(Tetromino::rotations[Tetromino::a_rot].fragments[i].p_y + Tetromino::posY < (board.height - 1)){
                    board.layout[Tetromino::rotations[Tetromino::a_rot].fragments[i].p_y + Tetromino::posY + 1][Tetromino::rotations[Tetromino::a_rot].fragments[i].p_x + Tetromino::posX] = Tetromino::rotations[Tetromino::a_rot].fragments[i];
                }else{
                    gameOver = true;
                }
            }
        }
        return collided;
    }
