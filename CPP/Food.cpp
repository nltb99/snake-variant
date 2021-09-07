//
//  Food.cpp
//  CPP
//
//  Created by nltbao on 28/08/2021.
//

#include "Food.hpp"
#include "Game.hpp"
#include "Snake.hpp"
#include <map>

int Food::posX, Food::posY;
int food_direction_options[4][3] = {
    {1,2,3}, // UP
    {0,2,3}, // DOWN
    {0,1,3}, // LEFT
    {0,1,2}, // RIGHT
};

bool Food::b_ate_food = true;

Food::Food()
    : rect({0, 0, Game::GRID_WIDTH, Game::GRID_WIDTH})
{}

Food::~Food(){}

void Food::generate_food()
{
    if(b_ate_food) {
        posX = std::rand() % Game::TOTAL_CELL;
        posY = std::rand() % Game::TOTAL_CELL;
 
        for(int i = 0; i < Snake::vt.size(); ++i){
            int x = Snake::vt[i].first.first;
            int y = Snake::vt[i].first.second;
            if((x == posX && y == posY) || (x == prevPosX && y == prevPosY)){
                Food::generate_food();
                return;
            }
            prevPosX = x;
            prevPosY = y;
        }
        b_ate_food = false;
    }
          
    rect.x = posY * Game::GRID_WIDTH;
    rect.y = posX * Game::GRID_WIDTH;
    SDL_SetRenderDrawColor(Game::renderer, 92, 11, 255, 255);
    SDL_RenderFillRect(Game::renderer, &rect);
    SDL_SetRenderDrawColor(Game::renderer, 92, 11, 255, 255);
    SDL_RenderDrawRect(Game::renderer, &rect);
}

void Food::run_away(){
    int rand_direction = std::rand() % 4;
    int rand_option = std::rand() % 3;
    if(
       (rand_direction == Direction.UP && last_food_direction == Direction.DOWN) ||
       (rand_direction == Direction.DOWN && last_food_direction == Direction.UP) ||
       (rand_direction == Direction.LEFT && last_food_direction == Direction.RIGHT) ||
       (rand_direction == Direction.RIGHT && last_food_direction == Direction.LEFT)
       ){
        rand_direction = last_food_direction;
    }
    
    if(rand_direction == Direction.UP){
        if(Food::posX <= 0) {
            rand_direction = food_direction_options[Direction.UP][rand_option];
            Food::move_food(rand_direction);
        } else{
            Food::move_food(Direction.UP);
        }
    }
    else if(rand_direction == Direction.DOWN){
        if(Food::posX + 1 >= Game::TOTAL_CELL){
            rand_direction = food_direction_options[Direction.DOWN][rand_option];
            Food::move_food(rand_direction);
        } else{
            Food::move_food(Direction.DOWN);
        }
    }
    else if(rand_direction == Direction.LEFT){
        if(Food::posY <= 0){
            rand_direction = food_direction_options[Direction.LEFT][rand_option];
            Food::move_food(rand_direction);
        } else{
            Food::move_food(Direction.LEFT);
        }
    }
    else if(rand_direction == Direction.RIGHT){
        if(Food::posY + 1 >= Game::TOTAL_CELL){
            rand_direction = food_direction_options[Direction.RIGHT][rand_option];
            Food::move_food(rand_direction);
        } else{
            Food::move_food(Direction.RIGHT);
        }
    }
    last_food_direction = rand_direction;
}

void Food::move_food(int direction){
    if(direction == Direction.UP){
        --Food::posX;
    } else if(direction == Direction.DOWN){
        ++Food::posX;
    } else if(direction == Direction.LEFT){
        --Food::posY;
    } else if(direction == Direction.RIGHT){
        ++Food::posY;
    }
}


