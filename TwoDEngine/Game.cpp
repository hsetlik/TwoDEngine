#include "Game.hpp"
//loading PNG images into textures
SDL_Texture *hiddenTile;
SDL_Texture *emptyTile;
SDL_Texture *flagTile;
SDL_Texture *mineTile;
//creating a rectangle the size of one tile
SDL_Rect tileRectSource;
SDL_Rect tileRectDest;

//Tile activeGrid[16][16];

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
        IMG_Init(IMG_INIT_PNG);
        printf("SDL_Img initialized\n");
        //verifies that SDL started up correctly
        printf("SDL Initialized\n");
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window){
            //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            printf("Window Created\n");
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            printf("Renderer Created\n");
        }
        isRunning = true;
    }
    //create a temporary surface for the image
    SDL_Surface *tempSurfaceEmpty = IMG_Load("/Users/SFMAdmin/Desktop/Programming/SDL_projects/TwoDEngine/TwoDEngine/PNG_Assets/empty_tileQuarter.png");
    //convert that temporary surface to a texture for actual use
    emptyTile = SDL_CreateTextureFromSurface(renderer, tempSurfaceEmpty);
    //gets rid of that temporary surface
    SDL_FreeSurface(tempSurfaceEmpty);
    //doing the above for the rest of the PNGs
    //the hidden tile
    SDL_Surface *tempSurfaceHidden = IMG_Load("/Users/SFMAdmin/Desktop/Programming/SDL_projects/TwoDEngine/TwoDEngine/PNG_Assets/flag_tileQuarter.png");
    hiddenTile = SDL_CreateTextureFromSurface(renderer, tempSurfaceHidden);
    SDL_FreeSurface(tempSurfaceHidden);
    //the flag tile
    SDL_Surface *tempSurfaceFlag = IMG_Load("/Users/SFMAdmin/Desktop/Programming/SDL_projects/TwoDEngine/TwoDEngine/PNG_Assets/hidden_tileQuarter.png");
    flagTile = SDL_CreateTextureFromSurface(renderer, tempSurfaceFlag);
    SDL_FreeSurface(tempSurfaceFlag);
    //the mine tile
    SDL_Surface *tempSurfaceMine = IMG_Load("/Users/SFMAdmin/Desktop/Programming/SDL_projects/TwoDEngine/TwoDEngine/PNG_Assets/mine_tileQuarter.png");
    mineTile = SDL_CreateTextureFromSurface(renderer, tempSurfaceMine);
    SDL_FreeSurface(tempSurfaceMine);
    printf("PNG files loaded to textures\n");
}
void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            //do stuff when the mouse is clicked
            break;
        // check for more events with more case statements here
        default:
            break;
    }
}
void Game::update()
{
    tileRectSource.h = 25;
    tileRectSource.w = 25;
    tileRectDest.h = 25;
    tileRectDest.w = 25;
}
void Game::render()
{
    SDL_RenderClear(renderer);
    //draw stuff here
    //SDL_RenderCopy(renderer, hiddenTile, &tileRectSource, &tileRectDest);
    SDL_RenderPresent(renderer);
}
void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
    printf("Game Cleaned\n");
}
// now for stuff from the tile class...
Tile:: Tile() {
    
}

Tile:: ~Tile() {
    
}

void Tile::init(int xpos, int ypos, int status) {
    _topLeftX = xpos * 25;
    _topLeftY = ypos * 25;
    switch (status) {
        case 0:
            _statusTexture = hiddenTile;
            break;
        case 1:
            _statusTexture = emptyTile;
            break;
        case 2:
            _statusTexture = flagTile;
            break;
        case 3:
            _statusTexture = mineTile;
            break;
        default:
            break;
    }
}

int Tile:: minesAdjacent(){
    int count = 0;
    //math to figure out how many mines are adjacent
    return count;
}

bool Tile:: hasMine() {
    bool isMine = _hasMine;
    return isMine;
}

