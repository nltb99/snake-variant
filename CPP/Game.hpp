//
//  Game.hpp
//  CPP
//
//  Created by nltbao on 02/08/2021.
//

#ifndef Game_hpp
#define Game_hpp
#include <SDL2/SDL.h>
#include <iostream>

class Game{
public:
    Game();
    ~Game();
    
    static const int SCREEN_WIDTH = 600;
    static const int SCREEN_HEIGHT = 600;
    static const int GRID_WIDTH = 25;
    static const int TOTAL_CELL = SCREEN_WIDTH / GRID_WIDTH;
    static std::pair<int, int> globalMap[TOTAL_CELL][TOTAL_CELL];

    static SDL_Renderer* renderer;
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    void drawMapVisual();
    void drawMapNonVisual();
    bool running(){ return isRunning; };
    
private:
    bool isRunning;
    SDL_Window *window;  
};

#endif /* Game_hpp */
