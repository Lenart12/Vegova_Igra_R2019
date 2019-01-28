#include <iostream>
#include <game.h>

Game *game = nullptr;

int main()
{
    const int FPS = 240;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("Izbrisi plastiko", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1240, 720, false);

    while(game->getRunning()){
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
