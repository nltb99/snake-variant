//
//  Snake.cpp
//  CPP
//
//  Created by nltbao on 28/08/2021.
//

#include "Snake.hpp"

std::vector<std::pair<std::pair<int, int>, int>> Snake::vt;

Snake::Snake()
    : rect({0, 0, Game::GRID_WIDTH, Game::GRID_WIDTH})
{
    vt.emplace_back(std::make_pair(std::make_pair(3, 2), Direction.RIGHT));
    Game::globalMap[3][2].first = 1;
}

Snake::~Snake()
{}

void Snake::drawSnake()
{
    for(int i = 0; i < vt.size(); ++i){
        rect.y = (vt[i].first.first) * Game::GRID_WIDTH;
        rect.x = (vt[i].first.second) * Game::GRID_WIDTH;
        SDL_SetRenderDrawColor(Game::renderer, 246, 255, 11, 255);
        SDL_RenderFillRect(Game::renderer, &rect);
        SDL_SetRenderDrawColor(Game::renderer, 246, 255, 11, 255);
        SDL_RenderDrawRect(Game::renderer, &rect);
    }
}

Snake::SNAKE_BODY Snake::get_snake_body()
{
    SNAKE_BODY snake_body;

    auto last_element = vt.end(); --last_element;
    auto first_element = vt.begin();
    
    snake_body.current_direction = (*last_element).second;
    
    snake_body.first_x = (*first_element).first.first;
    snake_body.first_y = (*first_element).first.second;
        
    snake_body.last_x = (*last_element).first.first;
    snake_body.last_y = (*last_element).first.second;

    return snake_body;
}

void Snake::move_up(bool bAuto)
{
    auto snake_body = Snake::get_snake_body();
    int x, y;
    if(
       snake_body.current_direction != Direction.DOWN &&
       (bAuto || snake_body.current_direction != Direction.UP)
       ){
        if(snake_body.last_x <= 0) {
            x = Game::TOTAL_CELL - 1;
            y = snake_body.last_y;
        } else {
            x = snake_body.last_x - 1;
            y = snake_body.last_y;
        }
        if(!Snake::b_Collison(x, y)){
            Snake:eraseTail(snake_body.first_x, snake_body.first_y, x, y);
            Snake::addHead(x, y, Direction.UP);
        }
    }
}

void Snake::move_down(bool bAuto)
{
    auto snake_body = Snake::get_snake_body();
    int x, y;
    if(
       snake_body.current_direction != Direction.UP &&
       (bAuto || snake_body.current_direction != Direction.DOWN)
       ){
        if(snake_body.last_x + 1 >= Game::TOTAL_CELL){
            x = 0;
            y = snake_body.last_y;
        } else {
            x = snake_body.last_x + 1;
            y = snake_body.last_y;
        }
        if(!Snake::b_Collison(x, y)){
            Snake:eraseTail(snake_body.first_x, snake_body.first_y, x, y);
            Snake::addHead(x, y, Direction.DOWN);
        }
    }
}

void Snake::move_left(bool bAuto)
{
    auto snake_body = Snake::get_snake_body();
    int x, y;
    if(
       snake_body.current_direction != Direction.RIGHT &&
       (bAuto || snake_body.current_direction != Direction.LEFT)
       ){
        if(snake_body.last_y <= 0){
            x = snake_body.last_x;
            y = Game::TOTAL_CELL - 1;
        } else {
            x = snake_body.last_x;
            y = snake_body.last_y - 1;
        }
        if(!Snake::b_Collison(x, y)){
            Snake:eraseTail(snake_body.first_x, snake_body.first_y, x, y);
            Snake::addHead(x, y, Direction.LEFT);
        }
    }
}

void Snake::move_right(bool bAuto)
{
    auto snake_body = Snake::get_snake_body();
    int x, y;
    if(
       snake_body.current_direction != Direction.LEFT &&
       (bAuto || snake_body.current_direction != Direction.RIGHT)
       ){
        if(snake_body.last_y + 1 >= Game::TOTAL_CELL){
            x = snake_body.last_x;
            y = 0;
        } else {
            x = snake_body.last_x;
            y = snake_body.last_y + 1;
        }
        if(!Snake::b_Collison(x, y)){
            Snake:eraseTail(snake_body.first_x, snake_body.first_y, x, y);
            Snake::addHead(x, y, Direction.RIGHT);
        }
    }
}

bool Snake::b_Collison(int x, int y)
{
    if(Game::globalMap[x][y].first == 1){
        return true;
    }
    return false;
}

bool Snake::b_EatFood(int x, int y)
{
    if(x == Food::posX && y == Food::posY){
        Food::b_ate_food = true;
        return true;
    }
    return false;
}

void Snake::eraseTail(int first_x, int first_y, int x, int y)
{
    if(!Snake::b_EatFood(x, y)){
        vt.erase(vt.begin());
        Game::globalMap[first_x][first_y].first = 0;
    }
}

void Snake::addHead(int x, int y, int direction)
{
    vt.emplace_back(std::make_pair(std::make_pair(x, y), direction));
    Game::globalMap[x][y].first = 1;
}

void Snake::autoCrawlFoward()
{
    auto last_element = vt.end(); --last_element;
    int current_direction = (*last_element).second;
    if(current_direction == Direction.UP){
        Snake::move_up(true);
    } else if(current_direction == Direction.DOWN){
        Snake::move_down(true);
    } else if(current_direction == Direction.LEFT){
        Snake::move_left(true);
    } else if(current_direction == Direction.RIGHT){
        Snake::move_right(true);
    }
    usleep(100 * 1000);
}

void Snake::autoCrawlAI()
{
    auto snake_body = Snake::get_snake_body();
    if(snake_body.current_direction == Direction.UP){
        if(snake_body.last_x <= Food::posX){
            if(snake_body.last_y > Food::posY){
                Snake::move_left(true);
            } else {
                Snake::move_right(true);
            }
        } else{
            Snake::move_up(true);
        }
    } else if (snake_body.current_direction == Direction.DOWN){
        if(snake_body.last_x >= Food::posX){
            if(snake_body.last_y > Food::posY){
                Snake::move_left(true);
            } else {
                Snake::move_right(true);
            }
        } else{
            Snake::move_down(true);
        }
    } else if (snake_body.current_direction == Direction.LEFT){
        if(snake_body.last_y <= Food::posY){
            if(snake_body.last_x < Food::posX){
                Snake::move_down(true);
            } else{
                Snake::move_up(true);
            }
        } else{
            Snake::move_left(true);
        }
    } else if (snake_body.current_direction == Direction.RIGHT){
        if(snake_body.last_y >= Food::posY){
            if(snake_body.last_x < Food::posX){
                Snake::move_down(true);
            } else{
                Snake::move_up(true);
            }
        } else{
            Snake::move_right(true);
        }
    }
    usleep(100 * 1000);
}

