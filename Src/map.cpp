#include <map.h>

#include <cstdlib>

Map::Map(int _w, int _h, int passes){
    w = _w;
    h = _h;
    seed();
    edgeTrim();
    pass(passes);
}

bool inBounds(int x, int y, int w, int h){
    return (x >= 0 && x < w && y >= 0 && y < h);
}

int Map::neighbours(int x , int y){
    int xm1 = x - 1;
    int xp1 = x + 1;
    int ym1 = y - 1;
    int yp1 = y + 1;
    int neighbours = 0;
    if(inBounds(xm1, ym1, w, h) && tiles.at(xm1).at(ym1) == 1) neighbours++;
    if(inBounds(xm1, y, w, h) && tiles.at(xm1).at(y) == 1) neighbours++;
    if(inBounds(xm1, yp1, w, h) && tiles.at(xm1).at(yp1) == 1) neighbours++;
    if(inBounds(x, ym1, w, h) && tiles.at(x).at(ym1) == 1) neighbours++;
    if(inBounds(x, yp1, w, h) && tiles.at(x).at(yp1) == 1) neighbours++;
    if(inBounds(xp1, ym1, w, h) && tiles.at(xp1).at(ym1) == 1) neighbours++;
    if(inBounds(xp1, y, w, h) && tiles.at(xp1).at(y) == 1) neighbours++;
    if(inBounds(xp1, yp1, w, h) && tiles.at(xp1).at(yp1) == 1) neighbours++;

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
        tiles.at(x).at(h - 1) = 0;
    }    
    for(int y = 0; y < h; y++){
        tiles.at(0).at(y) = 0;
        tiles.at(w - 1).at(y) = 0;
    }    
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

void Map::render(SDL_Renderer *renderer, int tileX, int tileY){
    SDL_Rect Drect;
    Drect.w = tileX;
    Drect.h = tileY;
    for(int x = 0; x < w; x++){
        Drect.x = x * tileX;
        for(int y = 0; y < h; y++){
            Drect.y = y * tileY;
            int type = tiles.at(x).at(y);
            type = (type == 1) ? 2 : 0;
            type += rand() % 2;
            SDL_Texture *tex = worldTexture.getTexture(type);
            SDL_RenderCopy(renderer,
                           tex,
                           NULL, &Drect);
        }
    }
}