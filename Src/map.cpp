#include <map.h>
#include <conf.h>

#include <cstdlib>
#include <algorithm>

Texture Map::worldTexture;

Map::Map(int _w, int _h, int passes, SDL_Renderer *renderer){
    w = _w;
    h = _h;
    seed();
    edgeTrim();
    pass(passes);
    populate();
    worldTexture.loadTextures("Texture\\morje1.png", renderer);
    worldTexture.loadTextures("Texture\\morje2.png", renderer);
    worldTexture.loadTextures("Texture\\kopno1.png", renderer);
    worldTexture.loadTextures("Texture\\kopno2.png", renderer);
    worldTexture.loadTextures("Texture\\obala1.png", renderer);
    worldTexture.loadTextures("Texture\\obala2.png", renderer);
    worldTexture.loadTextures("Texture\\obala3.png", renderer);
    land = drawLand(renderer);
}

Map::Map(int _w, int _h, std::vector< std::vector<int> > _tiles, SDL_Renderer *renderer){
    w = _w;
    h = _h;
    tiles = _tiles;
    worldTexture.loadTextures("Texture\\morje1.png", renderer);
    worldTexture.loadTextures("Texture\\morje2.png", renderer);
    worldTexture.loadTextures("Texture\\kopno1.png", renderer);
    worldTexture.loadTextures("Texture\\kopno2.png", renderer);
    worldTexture.loadTextures("Texture\\obala1.png", renderer);
    worldTexture.loadTextures("Texture\\obala2.png", renderer);
    worldTexture.loadTextures("Texture\\obala3.png", renderer);
    land = drawLand(renderer);
}

bool Map::inBounds(int x, int y){
    return (x >= 0 && x < w && y >= 0 && y < h);
}

int Map::neighbours(int x , int y){
    int xm1 = x - 1;
    int xp1 = x + 1;
    int ym1 = y - 1;
    int yp1 = y + 1;
    int neighbours = 0;
    if(inBounds(xm1, ym1) && tiles.at(xm1).at(ym1) == 1) neighbours++;
    if(inBounds(xm1, y) && tiles.at(xm1).at(y) == 1) neighbours++;
    if(inBounds(xm1, yp1) && tiles.at(xm1).at(yp1) == 1) neighbours++;
    if(inBounds(x, ym1) && tiles.at(x).at(ym1) == 1) neighbours++;
    if(inBounds(x, yp1) && tiles.at(x).at(yp1) == 1) neighbours++;
    if(inBounds(xp1, ym1) && tiles.at(xp1).at(ym1) == 1) neighbours++;
    if(inBounds(xp1, y) && tiles.at(xp1).at(y) == 1) neighbours++;
    if(inBounds(xp1, yp1) && tiles.at(xp1).at(yp1) == 1) neighbours++;

    return neighbours;
}

void Map::seed(){
    for(int x = 0; x < w; x++){
        std::vector<int> tmp;
        for(int y = 0; y < h; y++){
            tmp.push_back((rand() % 100 < 47) ? 1 : 0);
        }
        tiles.push_back(tmp);
    }    
}

void Map::edgeTrim(){
    for(int x = 0; x < w; x++){
        tiles.at(x).at(0) = 0;
        tiles.at(x).at((__int64)h - 1) = 0;
    }    
    for(int y = 0; y < h; y++){
        tiles.at(0).at(y) = 0;
        tiles.at((__int64)w - 1).at(y) = 0;
    }    
}

void Map::populate(){
    for(int x = 0; x < w; x++)
        for(int y = 0; y < h; y++)
            tiles.at(x).at(y) = (tiles.at(x).at(y) == 1 && rand() % 100 < 10) ? 2 : tiles.at(x).at(y); 
}

void Map::pass(int passes){
    while(passes-- != 0)
    {
        std::vector< std::vector<int> > newTiles(tiles);

        for(int x = 0; x < w; x++)
            for(int y = 0; y < h; y++){
                int n = neighbours(x, y);
                int sea = tiles.at(x).at(y); 
                if( (sea == 0 && n > 4) || (sea == 1 && n > 3) )
                    newTiles.at(x).at(y) = 1;
                else
                    newTiles.at(x).at(y) = 0;
            }
        tiles = newTiles;
    }
}

SDL_Texture* Map::drawLand(SDL_Renderer *renderer){
    SDL_Texture *obala1 = worldTexture.getTexture(4);
    SDL_Texture *obala2 = worldTexture.getTexture(5);
    SDL_Texture *obala3 = worldTexture.getTexture(6);

    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            int type = tiles.at(x).at(y);
            if(type > 0){
                type++;

                SDL_Texture *tex = worldTexture.getTexture(type);
                worldTexture.renderTile(x, y, tex, renderer);

                int xm1 = x - 1;
                int xp1 = x + 1;
                int ym1 = y - 1;
                int yp1 = y + 1;


                if(Type(x, ym1) == 0) worldTexture.renderTileRotation(x, y, 0, obala1, renderer);
                if(Type(xp1, y) == 0) worldTexture.renderTileRotation(x, y, 90, obala1, renderer);
                if(Type(x, yp1) == 0) worldTexture.renderTileRotation(x, y, 180, obala1, renderer);
                if(Type(xm1, y) == 0) worldTexture.renderTileRotation(x, y, 270, obala1, renderer);
                
                if(Type(xm1, ym1) == 0 && Type(x, ym1) == 0 && Type(xm1, y) == 0) worldTexture.renderTileRotation(x, y, 0, obala2, renderer);
                if(Type(xp1, ym1) == 0 && Type(x, ym1) == 0 && Type(xp1, y) == 0) worldTexture.renderTileRotation(x, y, 90, obala2, renderer);
                if(Type(xp1, yp1) == 0 && Type(x, yp1) == 0 && Type(xp1, y) == 0) worldTexture.renderTileRotation(x, y, 180, obala2, renderer);
                if(Type(xm1, yp1) == 0 && Type(x, yp1) == 0 && Type(xm1, y) == 0) worldTexture.renderTileRotation(x, y, 270, obala2, renderer);
                
                if(Type(xm1, ym1) == 0 && Type(x, ym1) > 0 && Type(xm1, y) > 0) worldTexture.renderTileRotation(x, y, 0, obala3, renderer);
                if(Type(xp1, ym1) == 0 && Type(x, ym1) > 0 && Type(xp1, y) > 0) worldTexture.renderTileRotation(x, y, 90, obala3, renderer);
                if(Type(xp1, yp1) == 0 && Type(x, yp1) > 0 && Type(xp1, y) > 0) worldTexture.renderTileRotation(x, y, 180, obala3, renderer);
                if(Type(xm1, yp1) == 0 && Type(x, yp1) > 0 && Type(xm1, y) > 0) worldTexture.renderTileRotation(x, y, 270, obala3, renderer);
            }
        }
    }
    static Conf conf;
    SDL_Surface *surface = SDL_CreateRGBSurface(0, conf.width, conf.height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return tex;
}

void Map::render(SDL_Renderer *renderer){
    SDL_RenderCopy(renderer, land, NULL, NULL);
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            int type = tiles.at(x).at(y);
            if(type == 0){
                type = 0 + (rand() % 100 < 33) ? 1 : 0;
                SDL_Texture *tex = worldTexture.getTexture(type);
                worldTexture.renderTile(x, y, tex, renderer);
            }
        }
    }
}

void Map::randomTile(int type, int &x, int &y){
    int tX, tY;
    while(true){
        tX = rand() % w;
        tY = rand() % h;
        if(tiles.at(tX).at(tY) == type){
            x = tX;
            y = tY;
            break;
        }
    }
}



void Map::randomTile(int type, int pos_x, int pos_y, int &x, int &y){
    std::vector<SDL_Point> possibleTiles;
    SDL_Point tmp;
    for(int iX = pos_x - 1; iX <= pos_x + 1; iX++){
        for(int iY = pos_y - 1; iY <= pos_y + 1; iY++){
            if(inBounds(iX, iY) && tiles.at(iX).at(iY) == type){
                tmp.x = iX;
                tmp.y = iY;
                possibleTiles.push_back(tmp);
            }
        }
    }
    if(possibleTiles.size() > 0){
        std::random_shuffle(possibleTiles.begin(), possibleTiles.end());

        x = possibleTiles.at(0).x;
        y = possibleTiles.at(0).y;
    }
}

void Map::randomTile(int pos_x, int pos_y, int &x, int &y){
    int type = tiles.at(pos_x).at(pos_y);

    std::vector<SDL_Point> possibleTiles;
    SDL_Point tmp;
    for(int iX = pos_x - 1; iX <= pos_x + 1; iX++){
        for(int iY = pos_y - 1; iY <= pos_y + 1; iY++){
            if(inBounds(iX, iY) && tiles.at(iX).at(iY) == type){
                tmp.x = iX;
                tmp.y = iY;
                possibleTiles.push_back(tmp);
            }
        }
    }
    if(possibleTiles.size() > 0){
        std::random_shuffle(possibleTiles.begin(), possibleTiles.end());

        x = possibleTiles.at(0).x;
        y = possibleTiles.at(0).y;
    }
}

int Map::Type(int pos_x, int pos_y){
    return (inBounds(pos_x, pos_y)) ? tiles.at(pos_x).at(pos_y) : -1;
}