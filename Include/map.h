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
    void populate();
    void pass(int);
protected:
    std::vector< std::vector<int> > tiles;
public:
    static Texture worldTexture;
    Map(int, int, int);
    void render(SDL_Renderer*);
};

#endif