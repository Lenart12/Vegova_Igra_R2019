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

    worldTexture.loadTextures("Texture/morje1.png", renderer);
    worldTexture.loadTextures("Texture/morje2.png", renderer);
    worldTexture.loadTextures("Texture/kopno1.png", renderer);
    worldTexture.loadTextures("Texture/kopno2.png", renderer);
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
        tiles.at(x).at(h - 1) = 0;
    }    
    for(int y = 0; y < h; y++){
        tiles.at(0).at(y) = 0;
        tiles.at(w - 1).at(y) = 0;
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

void Map::render(SDL_Renderer *renderer){
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            int type = tiles.at(x).at(y);
            switch (type){
                case 0:
                    type = 0 + (rand() % 100 < 33) ? 1 : 0;
                    break;
                case 1:
                    type = 2;
                    break;
                case 2:
                    type = 3;
                    break;
            }
            SDL_Texture *tex = worldTexture.getTexture(type);
            worldTexture.renderTile(x, y, tex, renderer);
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
    std::random_shuffle(possibleTiles.begin(), possibleTiles.end());

    x = possibleTiles.at(0).x;
    y = possibleTiles.at(0).y;
}

int Map::Type(int pos_x, int pos_y){
    return tiles.at(pos_x).at(pos_y);
}