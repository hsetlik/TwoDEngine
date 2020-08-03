#include "Game.hpp"

Game::Game() {
    
}
Game::~Game() {
    
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        //verifies that SDL started up correctly
        printf("SDL Initialized\n");
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window){
            //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            printf("Window Created\n");
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            printf("Renderer Created\n");
        }
        isRunning = true;
    } else {
        isRunning = false;
    }
}
void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        // check for more events with more case statements here
        default:
            break;
    }
}
void Game::update()
{}
void Game::render()
{
    SDL_RenderClear(renderer);
    //draw stuff here
    SDL_RenderPresent(renderer);
}
void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    printf("game cleaned\n");
}
