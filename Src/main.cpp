#include <game.h>
#include <conf.h>

#include <iostream>
#include <cstdlib>
#include <ctime>

std::string textInput;

int main(int argc, char* argv[])
{
    srand(time(0));
    static Conf conf;
    const int FPS = conf.gameFps;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

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
