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
#include "/Library/Frameworks/SDL2_image.framework/Headers/SDL_image.h"
#include <stdio.h>
#include <fstream>
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
    int _redlevel = 255;
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer * renderer;
};

class Tile{
public:
    Tile();
    ~Tile();
    void init(int xpos, int ypos, int status);
    bool isAdjacentTo(int xpos, int ypos);
    int minesAdjacent();
    int xPosition;
    int yPosition;
    bool hasMine();
    void placeMine();
    void reveal();
    void placeFlag();
    void renderStatus();
    void render(SDL_Renderer *thisRenderer);
    SDL_Rect tileRectSource;
    SDL_Rect tileRectDest;
private:
    SDL_Rect _tileRect;
    SDL_Texture *_statusTexture;
    int _xpos;
    int _ypos;
    int _XtopLeftpx;
    int _YtopLeftpx;
    bool _hasMine;
};



#endif /* Game_hpp */
