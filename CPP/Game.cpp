//
//  Game.cpp
//  CPP
//
//  Created by nltbao on 02/08/2021.
//

#include "Game.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include <utility>
#include <time.h>
#include <vector>

SDL_Renderer* Game::renderer = nullptr;
std::pair<int, int> Game::globalMap[TOTAL_CELL][TOTAL_CELL];

Game::Game(){
    Game::drawMapNonVisual();
}
Game::~Game(){}

Snake* snake = nullptr;
Food* food = nullptr;

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        
        snake = new Snake();
        food = new Food();
              
        isRunning = true;
    } else{
        isRunning = false;
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch( event.type ){
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym) {
                    case SDLK_LEFT:
                        snake->move_left(false);
                        break;
                    case SDLK_RIGHT:
                        snake->move_right(false);
                        break;
                    case SDLK_DOWN:
                        snake->move_down(false);
                        break;
                    case SDLK_UP:
                        snake->move_up(false);
                        break;
                }
        }
    }
};

void Game::update()
{
//    snake->autoCrawlFoward();
    snake->autoCrawlAI();
    food->run_away();
};

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    Game::drawMapVisual();
    snake->drawSnake();
    food->generate_food();
    SDL_RenderPresent(renderer);
};

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit(); 
};

void Game::drawMapVisual()
{
    for(int i=0; i < Game::SCREEN_HEIGHT + Game::GRID_WIDTH; i += Game::GRID_WIDTH){
        for(int j=0; j < Game::SCREEN_WIDTH + Game::GRID_WIDTH; j += Game::GRID_WIDTH){
            SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
            SDL_RenderDrawLine(Game::renderer, j, 0, j, Game::SCREEN_WIDTH);
        }
        SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(Game::renderer, 0, i, Game::SCREEN_WIDTH, i);
    }
}

void Game::drawMapNonVisual()
{
    for(int i = 0; i < TOTAL_CELL; ++i){
        for(int j = 0; j < TOTAL_CELL; ++j){
            globalMap[i][j].first = 0;
            globalMap[i][j].second = 999;
        }
    }
}

