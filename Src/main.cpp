#include <game.h>
#include <conf.h>

#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(0));
    const int FPS = 240;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    Conf conf;

    Game *game = new Game();
    game->init();

    while(game->Running()){
        frameStart = SDL_GetTicks();

        game->handleEvent();
        game->update();
        game->render();
        
        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }
    delete game;
    return 0;
}
