#include "Game.hpp"
//loading PNG images into textures
SDL_Texture *hiddenTile;
SDL_Texture *emptyTile;
SDL_Texture *flagTile;
SDL_Texture *mineTile;

int gridWidth = 16;
int gridHeight = 16;
int tileWidth = 25;
int tileHeight = 25;

//making a grid of tile objects at the initialization of the game
Tile activeGrid[16][16];

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
    SDL_Surface *tempSurfaceHidden = IMG_Load("/Users/SFMAdmin/Desktop/Programming/SDL_projects/TwoDEngine/TwoDEngine/PNG_Assets/hidden_tileQuarter.png");
    hiddenTile = SDL_CreateTextureFromSurface(renderer, tempSurfaceHidden);
    SDL_FreeSurface(tempSurfaceHidden);
    //the flag tile
    SDL_Surface *tempSurfaceFlag = IMG_Load("/Users/SFMAdmin/Desktop/Programming/SDL_projects/TwoDEngine/TwoDEngine/PNG_Assets/flag_tileQuarter.png");
    flagTile = SDL_CreateTextureFromSurface(renderer, tempSurfaceFlag);
    SDL_FreeSurface(tempSurfaceFlag);
    //the mine tile
    SDL_Surface *tempSurfaceMine = IMG_Load("/Users/SFMAdmin/Desktop/Programming/SDL_projects/TwoDEngine/TwoDEngine/PNG_Assets/mine_tileQuarter.png");
    mineTile = SDL_CreateTextureFromSurface(renderer, tempSurfaceMine);
    SDL_FreeSurface(tempSurfaceMine);
    printf("PNG files loaded to textures\n");
    for(int x = 0; x < 16; x++){
        for(int y = 0; y < 16; y++){
            activeGrid[x][y].init(x, y, 0);
        }
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
}
void Game::render()
{
    //printf("render started\n");
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, activeGrid[3][2]._statusTexture, &activeGrid[3][2].tileRectSource, &activeGrid[3][2].tileRectDest);
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16 ; y++) {
            printf("Preparing to render at: %d, %d \n", x, y);
            SDL_Texture *chosenTexture = activeGrid[x][y]._statusTexture;
            SDL_RenderCopy(renderer, chosenTexture, &activeGrid[x][y].tileRectSource, &activeGrid[x][y].tileRectDest);
            printf("RenderCopy complete at: %d, %d \n", x, y);
            SDL_RenderPresent(renderer);
        }
    }
    //printf("ready to present renderer \n");
    
    //printf("render finished\n");
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
    _XtopLeftpx= xpos * 25;
    _YtopLeftpx = ypos * 25;
    _xpos = xpos;
    _ypos = ypos;
    xPosition = xpos;
    yPosition = ypos;
    SDL_Rect tileRectSource;
    SDL_Rect tileRectDest;
    tileRectSource.w = tileWidth;
    tileRectSource.h = tileHeight;
    tileRectSource.x = _XtopLeftpx;
    tileRectSource.y = _YtopLeftpx;
    tileRectDest.x = _XtopLeftpx;
    tileRectDest.y = _YtopLeftpx;
    tileRectDest.w = tileWidth;
    tileRectDest.h = tileHeight;
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
    printf("Tile initialized at: %d, %d\n", xPosition, yPosition);
}

//checks if this tile instance is adjacent to the tile at xpos, ypos
bool Tile::isAdjacentTo(int xpos, int ypos){
    Tile adjacentSpaces[8];
    //adjacent spaces array wraps clockwise from top left corner
    adjacentSpaces[0] = activeGrid[_xpos - 1][_ypos - 1]; //top left
    adjacentSpaces[1] = activeGrid[_xpos][_ypos - 1]; //top center
    adjacentSpaces[2] = activeGrid[_xpos + 1][_ypos - 1];// top right
    adjacentSpaces[3] = activeGrid[_xpos + 1][_ypos]; // center right
    adjacentSpaces[4] = activeGrid[_xpos + 1][_ypos + 1]; // bottom right
    adjacentSpaces[5] = activeGrid[_xpos][_ypos + 1]; //bottom center
    adjacentSpaces[6] = activeGrid[_xpos - 1][_ypos + 1]; //bottom left
    adjacentSpaces[7] = activeGrid[_xpos - 1][_ypos]; // center left
    
    for (int i = 0; i < 8; i++) {
        if (adjacentSpaces[i].xPosition == activeGrid[xpos][ypos].xPosition) {
            if(adjacentSpaces[i].yPosition == activeGrid[xpos][ypos].yPosition){
                return true;
                break;
            }
        }
    }
    return false;
}
int Tile:: minesAdjacent(){
    int count = 0;
    Tile adjacentSpaces[8];
    //adjacent spaces array wraps clockwise from top left corner
    adjacentSpaces[0] = activeGrid[_xpos - 1][_ypos - 1]; //top left
    adjacentSpaces[1] = activeGrid[_xpos][_ypos - 1]; //top center
    adjacentSpaces[2] = activeGrid[_xpos + 1][_ypos - 1];// top right
    adjacentSpaces[3] = activeGrid[_xpos + 1][_ypos]; // center right
    adjacentSpaces[4] = activeGrid[_xpos + 1][_ypos + 1]; // bottom right
    adjacentSpaces[5] = activeGrid[_xpos][_ypos + 1]; //bottom center
    adjacentSpaces[6] = activeGrid[_xpos - 1][_ypos + 1]; //bottom left
    adjacentSpaces[7] = activeGrid[_xpos - 1][_ypos]; // center left
    for(int i = 0; i < 8; i++){
        if(adjacentSpaces[i].hasMine()){
            count++;
        }
    }
    return count;
}
void Tile:: tileRender(SDL_Renderer *thisRenderer)
{
    SDL_RenderCopy(thisRenderer, _statusTexture, &_tileRectSource, &_tileRectDest);
    printf("rendered tile at: %d, %d\n", _xpos, _ypos);
}
bool Tile:: hasMine() {
    bool isMine = _hasMine;
    return isMine;
}
void Tile:: placeMine() {
    _hasMine = true;
}
