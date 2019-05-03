#ifndef MAP_H
#define MAP_H

#include <texture.h>

#include <SDL.h>
#include <vector>

class Map{
private:
    int w, h;

    int neighbours(int, int);
    void seed();
    void edgeTrim();
    void populate();
    void pass(int);
    bool inBounds(int, int);
    SDL_Texture* drawLand(SDL_Renderer*);
    std::vector< std::vector<int> > tiles;
    SDL_Texture *land;
    static Texture worldTexture;
public:
    int W() {return w; }; 
    int H() {return h; }; 
    std::vector< std::vector<int> > Tiles() {return tiles; };
    int Type(int, int);
    Map(int, int, int, SDL_Renderer*);
    Map(int _w, int _h, std::vector< std::vector<int> > _tiles, SDL_Renderer *renderer);
    void randomTile(int, int&, int&);
    void randomTile(int, int, int&, int&);
    void randomTile(int, int, int, int&, int&);
    void render(SDL_Renderer*);
};

#endif