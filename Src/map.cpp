#include <map.h>

#include <cstdlib>

Map::Map(int _w, int _h, int passes){
    w = _w;
    h = _h;
    seed();
    pass(passes);
}


int Map::neighbours(int x , int y){
    int xm1 = x - 1;
    int xp1 = x + 1;
    int ym1 = y - 1;
    int yp1 = y + 1;
    int neighbours = 0;
    if(xm1 >= 0  && ym1 >= 0 && tiles.at(xm1).at(ym1) == 1) neighbours++;
    if(xm1 >= 0  && y >= 0 && tiles.at(xm1).at(y) == 1) neighbours++;
    if(xm1 >= 0  && yp1 < w && tiles.at(xm1).at(yp1) == 1) neighbours++;
    if(x >= 0  && ym1 >= 0 && tiles.at(x).at(ym1) == 1) neighbours++;
    if(x >= 0  && yp1 < w && tiles.at(x).at(yp1) == 1) neighbours++;
    if(xp1 < h  && ym1 >= 0 && tiles.at(xp1).at(ym1) == 1) neighbours++;
    if(xp1 < h  && y >= 0 && tiles.at(xp1).at(y) == 1) neighbours++;
    if(xp1 < h  && yp1 < w && tiles.at(xp1).at(yp1) == 1) neighbours++;
    return neighbours;
}

void Map::seed(){
    for(int x = 0; x < h; x++){
        std::vector<int> tmp;
        for(int y = 0; y < w; y++){
            tmp.push_back((rand() % 100 < 40) ? 1 : 0);
        }
        tiles.push_back(tmp);
    }    
}


void Map::pass(int passes){
    while(passes-- != 0)
    {
        std::vector< std::vector<int> > newTiles(tiles);

        for(int x = 0; x < h; x++)
            for(int y = 0; y < w; y++){
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
    for(int x = 0; x < h; x++){
        Drect.x = x * tileX;
        for(int y = 0; y < w; y++){
            Drect.y = y * tileY;
            SDL_RenderCopy(renderer,
                           worldTexture.getTexture(
                               tiles.at(x).at(y)
                           ),
                           NULL, &Drect);
        }
    }
}