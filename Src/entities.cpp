#include <entities.h>
#include <conf.h>

#include <iostream>

Entities::Entities(int enemyCnt, int trashCnt, int animalCnt, Map *level, SDL_Renderer* renderer){
    Conf conf;
    int x, y;
    level->randomTile(0, x, y);
    player = new Player(x, y);
    for(int i = 0; i < enemyCnt; i++)
    {
        level->randomTile(1, x, y);
        enemies.push_back(new Enemy(x, y));
    }
    for(int i = 0; i < trashCnt; i++)
    {
        level->randomTile(0, x, y);
        trash.push_back(new Trash(x, y));
    }
    for(int i = 0; i < animalCnt; i++)
    {
        level->randomTile(1, x, y);
        animals.push_back(new Animal(x, y));
    }
    
    playerTexture.loadTextures("Texture/player1.png", renderer);
    playerTexture.loadTextures("Texture/player2.png", renderer);
    playerTexture.loadTextures("Texture/ladja.png", renderer);

    enemyTexture.loadTextures("Texture/enemy.png", renderer);

    trashTexture.loadTextures("Texture/trash.png", renderer);

    animalTexture.loadTextures("Texture/rakec1.png", renderer);
    animalTexture.loadTextures("Texture/rakec2.png", renderer);
}

void Entities::update(Map* level){
    player->update(level);

    for(std::vector<Enemy*> :: iterator i = enemies.begin(); i < enemies.end(); i++)
    {
        (*i)->update(level);
    }
    
    for(std::vector<Trash*> :: iterator i = trash.begin(); i < trash.end(); i++)
    {
        (*i)->update(level);
    }
    
    for(std::vector<Animal*> :: iterator i = animals.begin(); i < animals.end(); i++)
    {
        (*i)->update(level);
    }

    checkColision();
}

void Entities::render(SDL_Renderer *renderer){
    SDL_Texture *tex;
    int pos_x, pos_y,
        textureIndex;

    pos_x = player->X();
    pos_y = player->Y();
    textureIndex = player->TextureIndex();
    tex = playerTexture.getTexture(textureIndex);
    playerTexture.renderTile(pos_x, pos_y, tex, renderer);

    for(std::vector<Enemy*> :: iterator i = enemies.begin(); i < enemies.end(); i++)
    {
        pos_x = (*i)->X();
        pos_y = (*i)->Y();
        textureIndex = (*i)->TextureIndex();
        tex = enemyTexture.getTexture(textureIndex);
        enemyTexture.renderTile(pos_x, pos_y, tex, renderer);
    }
    
    for(std::vector<Trash*> :: iterator i = trash.begin(); i < trash.end(); i++)
    {
        pos_x = (*i)->X();
        pos_y = (*i)->Y();
        textureIndex = (*i)->TextureIndex();
        tex = trashTexture.getTexture(textureIndex);
        trashTexture.renderTile(pos_x, pos_y, tex, renderer);
    }
    
    for(std::vector<Animal*> :: iterator i = animals.begin(); i < animals.end(); i++)
    {
        pos_x = (*i)->X();
        pos_y = (*i)->Y();
        textureIndex = (*i)->TextureIndex();
        tex = animalTexture.getTexture(textureIndex);
        animalTexture.renderTile(pos_x, pos_y, tex, renderer);
    }
}
void Entities::checkColision(){
    int tX, tY;
    tX = player->X();
    tY = player->Y();

    for(std::vector<Enemy*> :: iterator i = enemies.begin(); i < enemies.end(); i++)
    {
        if( (*i)->X() == tX && (*i)->Y() == tY )
            std::cout<< "Player hit enemy" << std::endl;
    }
    
    for(std::vector<Trash*> :: iterator i = trash.begin(); i < trash.end(); i++)
    {
        if( (*i)->X() == tX && (*i)->Y() == tY ){
            trash.erase(i);
            std::cout<< "Player hit trash" << std::endl;
        }
    }
    
    for(std::vector<Animal*> :: iterator i = animals.begin(); i < animals.end(); i++)
    {
        if( (*i)->X() == tX && (*i)->Y() == tY ){
            animals.erase(i);
            std::cout<< "Player saved crab" << std::endl;
        }
    }
}

bool Entities::checkBounds(int targetX, int targetY){
    Conf conf;

    if(targetX < 0 ||
       targetY < 0 ||
       targetX >= conf.tileCntX ||
       targetY >= conf.tileCntY)
        return false;

    return true;
}

void Entities::move(std::string selector, int pos_x, int pos_y){
    int absX, absY;

    if(selector[0] == 'p'){    // player
        absX = player->X() + pos_x;
        absY = player->Y() + pos_y;
        if(checkBounds(absX, absY)){
            player->X(absX);
            player->Y(absY);
        }
    }
    else{
        int index = std::stoi(selector.erase(1, 1));
        
        if(selector[0] == 'e'){    // enemy
            absX = enemies.at(index)->X() + pos_x;
            absY = enemies.at(index)->Y() + pos_y;
            if(checkBounds(absX, absY)){
                enemies.at(index)->X(absX);
                enemies.at(index)->Y(absY);
            }
        }
        else if(selector[0] == 't'){    // trash
            absX = trash.at(index)->X() + pos_x;
            absY = trash.at(index)->Y() + pos_y;
            if(checkBounds(absX, absY)){
                trash.at(index)->X(absX);
                trash.at(index)->Y(absY);
            }
        }
        else if(selector[0] == 'a'){    // animal
            absX = animals.at(index)->X() + pos_x;
            absY = animals.at(index)->Y() + pos_y;
            if(checkBounds(absX, absY)){
                animals.at(index)->X(absX);
                animals.at(index)->Y(absY);
            }
        }
    }
}