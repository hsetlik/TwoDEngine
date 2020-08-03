//
//  main.cpp
//  TwoDEngine
//
//  Created by Hayden on 7/31/20.
//  Copyright © 2020 Hayden. All rights reserved.
//

#include <iostream>
#include "Game.hpp"


Game *game= nullptr;

int main(int argc, const char * argv[]) {
    game = new Game();
    game-> init("TestEngine", 600, 600, 600, 600, false);
    while(game->running()){
        game->handleEvents();
        game->update();
        game->render();
    }
    game->clean();
    return 0;
}


