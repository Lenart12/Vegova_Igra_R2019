#ifndef MAP_H
#define MAP_H

#include <texture.h>

#include <SDL2/SDL.h>
#include <vector>

class Map{
private:
    int w, h;


    int neighbours(int, int);
    void seed();
    void edgeTrim();
protected:
    std::vector< std::vector<int> > tiles;
public:
    void pass(int);
    Texture worldTexture;
    Map(int, int, int);
    void render(SDL_Renderer*, int, int);
};

#endif