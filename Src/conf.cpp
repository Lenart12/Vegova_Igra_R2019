#include <conf.h>
#include <SDL2/SDL.h>

Conf::Conf(){
    tileX = 16;
    tileY = 16;
    tileCntX = 80;
    tileCntY = 50;
    title = "Izbrisi plastiko";
    xpos = SDL_WINDOWPOS_CENTERED;
    ypos = SDL_WINDOWPOS_CENTERED;
    width = tileX * tileCntX;
    height = tileY * tileCntY;
    fullscreen = false;
    flags = 0;
    enemyCnt = 5;
    trashCnt = 10;
    animalCnt = 3;
}