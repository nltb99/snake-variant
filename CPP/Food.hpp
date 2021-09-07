//
//  Food.hpp
//  CPP
//
//  Created by nltbao on 28/08/2021.
//

#ifndef Food_hpp
#define Food_hpp
#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>

class Food {
public:
    Food();
    ~Food();
    
    SDL_Rect rect;
    static bool b_ate_food;
    static int posX, posY;
    
    void generate_food();
    void run_away();
    void move_food(int direction);
private:
    int prevPosX, prevPosY, last_food_direction;
    
    struct Direction {
        const int UP = 0;
        const int DOWN = 1;
        const int LEFT = 2;
        const int RIGHT = 3;
    } Direction;
    
};


#endif /* Food_hpp */
