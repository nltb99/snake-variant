//
//  Snake.hpp
//  CPP
//
//  Created by nltbao on 28/08/2021.
//

#ifndef Snake_hpp
#define Snake_hpp
#include <SDL2/SDL.h>
#include "Game.hpp"
#include "Food.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <unistd.h>

class Snake{
public:
    Snake();
    ~Snake();
    
    struct SNAKE_BODY {
        int first_x, first_y, last_x, last_y, current_direction;
    };

    static std::vector<std::pair<std::pair<int, int>, int>> vt;    
    
    SNAKE_BODY get_snake_body();
    void drawSnake();
    void move_up(bool bAuto);
    void move_down(bool bAuto);
    void move_left(bool bAuto);
    void move_right(bool bAuto);
    bool b_Collison(int x, int y);
    bool b_EatFood(int x, int y);
    void eraseTail(int first_x, int first_y, int x, int y);
    void addHead(int x, int y, int direction);
    void autoCrawlFoward();
    void autoCrawlAI();
private:
    SDL_Rect rect;
    
    struct Direction {
        const int UP = 0;
        const int DOWN = 1;
        const int LEFT = 2;
        const int RIGHT = 3;
    } Direction;
    
};

#endif /* Snake_hpp */
