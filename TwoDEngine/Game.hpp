//
//  Game.hpp
//  TwoDEngine
//
//  Created by Hayden on 7/31/20.
//  Copyright © 2020 Hayden. All rights reserved.
//
#ifndef Game_hpp
#define Game_hpp
#include "/Library/Frameworks/SDL2.framework/Versions/A/Headers/SDL.h"
#include <stdio.h>
class Game{
public:
    Game();
    ~Game();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    //handles user inputs and whatever the hell else
    void handleEvents();
    //updates all game objects
    void update();
    //draws appropriate graphics based on updated game logic
    void render();
    //manages memory
    void clean();
    bool running() {return isRunning;}
private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer * renderer;
};



#endif /* Game_hpp */
