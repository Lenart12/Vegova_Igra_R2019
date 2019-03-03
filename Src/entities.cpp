#include <entities.h>
#include <conf.h>

#include <cmath>
#include <iostream>

Entities::Entities(int enemyCnt, int trashCnt, int animalCnt, int zaveznikCnt, Map *_level, SDL_Renderer* renderer){
    Conf conf;
    int x, y;

    level = _level;

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
    for(int i = 0; i < zaveznikCnt; i++)
    {
        level->randomTile(rand() % 2, x, y);
        zavezniki.push_back(new Zaveznik(x, y));
    }
    
    playerTexture.loadTextures("Texture/player1.png", renderer);
    playerTexture.loadTextures("Texture/player2.png", renderer);
    playerTexture.loadTextures("Texture/ladja1.png", renderer);
    playerTexture.loadTextures("Texture/ladja2.png", renderer);

    enemyTexture.loadTextures("Texture/enemy1.png", renderer);
    enemyTexture.loadTextures("Texture/enemy2.png", renderer);

    trashTexture.loadTextures("Texture/trash1.png", renderer);
    trashTexture.loadTextures("Texture/trash2.png", renderer);

    animalTexture.loadTextures("Texture/rakec1.png", renderer);
    animalTexture.loadTextures("Texture/rakec2.png", renderer);

    zaveznikTexture.loadTextures("Texture/zaveznik1.png", renderer);
    zaveznikTexture.loadTextures("Texture/zaveznik2.png", renderer);
    zaveznikTexture.loadTextures("Texture/zaveznik3.png", renderer);
    zaveznikTexture.loadTextures("Texture/zaveznik4.png", renderer);

    fog.loadTextures("Texture/fog1.png", renderer);
    fog.loadTextures("Texture/fog2.png", renderer);
}

int Entities::update(){
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

    for(std::vector<Zaveznik*> :: iterator i = zavezniki.begin(); i < zavezniki.end(); i++)
    {
        (*i)->update(level);
    }

    if(trash.size() == 0 && animals.size() == 0 && enemies.size() == 0)
        return -10001;
    else
        return checkColision();
}

void Entities::render(SDL_Renderer *renderer){
    SDL_Texture *tex;
    Conf conf;
    int pos_x, pos_y,
        textureIndex;

    pos_x = player->X();
    pos_y = player->Y();
    textureIndex = player->TextureIndex();
    tex = playerTexture.getTexture(textureIndex);
    playerTexture.renderTile(pos_x, pos_y, tex, renderer);
    if(player->ladja_x != pos_x || player->ladja_y != pos_y){
        playerTexture.renderTile(player->ladja_x, player->ladja_y, playerTexture.getTexture(2), renderer);
    }

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
    
    for(std::vector<Zaveznik*> :: iterator i = zavezniki.begin(); i < zavezniki.end(); i++)
    {
        pos_x = (*i)->X();
        pos_y = (*i)->Y();
        textureIndex = (*i)->TextureIndex();
        tex = zaveznikTexture.getTexture(textureIndex);
        animalTexture.renderTile(pos_x, pos_y, tex, renderer);
    }

    for(int x = 0; x < conf.tileCntX; x++)
    {
        for(int y = 0; y < conf.tileCntY; y++)
        {
            int alpha;

            alpha = sqrt(pow(x - player->X(), 2) + pow(y - player->Y(), 2)) * 32;
            if(alpha > 255)
                alpha = 255;

            tex = fog.getTexture(rand() % 2);
            SDL_SetTextureAlphaMod(tex, alpha);
            fog.renderTile(x, y, tex, renderer);
        }
        
    }
    
}

Collision::Collision(std::string _selector, int _pos_x, int _pos_y){
    selector = _selector;
    pos_x = _pos_x;
    pos_y = _pos_y;
}

std::vector<Collision> Entities::listEntites(){
    std::vector<Collision> entites;

    entites.push_back(*(new Collision("p", player->X(), player->Y())));
    int i = 0;
    for(std::vector<Enemy*> :: iterator it = enemies.begin(); it < enemies.end(); it++){
        auto tmp = *(it);
        entites.push_back(*(new Collision("e" + std::to_string(i++), tmp->X(), tmp->Y())));
    }
    i = 0;
    for(std::vector<Trash*> :: iterator it = trash.begin(); it < trash.end(); it++){
        auto tmp = *(it);
        entites.push_back(*(new Collision("t" + std::to_string(i++), tmp->X(), tmp->Y())));
    }
    i = 0;
    for(std::vector<Animal*> :: iterator it = animals.begin(); it < animals.end(); it++){
        auto tmp = *(it);
        entites.push_back(*(new Collision("a" + std::to_string(i++), tmp->X(), tmp->Y())));
    }
    i = 0;
    for(std::vector<Zaveznik*> :: iterator it = zavezniki.begin(); it < zavezniki.end(); it++){
        auto tmp = *(it);
        entites.push_back(*(new Collision("z" + std::to_string(i++), tmp->X(), tmp->Y())));
    }

    return entites;
}

void Entities::splitSelector(std::string selector, char& t1, int& i1, char& t2, int& i2){
    t1 = selector[0];
    selector = selector.erase(0, 1);
    int mid = selector.find('-');

    if(mid == -1){
        if(selector.size() != 0)
            i1 = std::stoi(selector);
        t2 = -1;
        i2 = -1;
    }
    else{
        if(mid > 0)
            i1 = std::stoi(selector.substr(0, mid));
        else{
            i1 = -1;
        }
        selector = selector.erase(0, mid + 1);
        t2 = selector[0];
        selector = selector.erase(0, 1);
        if(selector.size() != 0){
            i2 = std::stoi(selector);
        }
        else{
            i2 = -1;
        }
    }
}

std::vector<Collision> Entities::findCollisions(){
    std::vector<Collision> entites = listEntites();
    std::vector<Collision> collisions;

    for(int i = 0; i < entites.size(); i++){
        for(int j = i + 1; j < entites.size(); j++){
            if(entites.at(i).pos_x == entites.at(j).pos_x &&
               entites.at(i).pos_y == entites.at(j).pos_y){
                Collision tmp(entites.at(i).selector + "-" + entites.at(j).selector,
                              entites.at(i).pos_x,
                              entites.at(i).pos_y);
                collisions.push_back(tmp);
            }
        }
    }

    return collisions;
}

int Entities::checkColision(){
    std::vector<Collision> collisons = findCollisions();
    
    if(collisons.size() != 0){
        for(int i = 0; i < collisons.size(); i++){
            Collision c = collisons.at(i);
            char t1, t2;
            int i1, i2;
            splitSelector(c.selector, t1, i1, t2, i2);
            if(t1=='p'){
                if(t2 == 'e'){
                    std::vector<Enemy*> :: iterator it = enemies.begin();
                    while(i2-- != 0) it++;
                    Enemy *e = *it;
                    int x1, x2, y1, y2;
                    x1 = e->X();
                    y1 = e->Y();
                    for(std::vector<Enemy*> :: iterator it2 = enemies.begin(); it2 != enemies.end(); it2++){
                        e = *it;
                        x2 = e->X();
                        y2 = e->Y();
                        if(x1 > x2 - 1 && x1 <= x2 + 1 &&
                           y1 > y2 - 1 && y2 <= y2 + 1 &&
                           x1 != x2 && y1 != y2){
                            return -10000;
                        }
                    }
                    enemies.erase(it);
                    return 50;
                }
                else if(t2=='t'){
                    std::vector<Trash*> :: iterator it = trash.begin();
                    while(i2-- != 0) it++;
                    trash.erase(it);
                    return 20;
                }
                else if(t2=='a'){
                    std::vector<Animal*> :: iterator it = animals.begin();
                    while(i2-- != 0) it++;
                    animals.erase(it);
                    return 30;
                }
                else if(t2=='z'){
                    std::vector<Zaveznik*> :: iterator it = zavezniki.begin();
                    while(i2-- != 0) it++;
                    zavezniki.erase(it);
                    return -100;
                }
            }
        }
    }
    return 0;
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

void Entities::move(int pos_x, int pos_y){
    int absX, absY, x, y;

    x = player->X(),
    y = player->Y(); 
    absX = x + pos_x;
    absY = y + pos_y;
    if(checkBounds(absX, absY)){
        int type = level->Type(x, y);
        int desttype = level->Type(absX, absY);
        if(type != 0 && desttype == 0){
            if(absX != player->ladja_x ||
                absY != player->ladja_y)
                return;
            else{
                player->X(absX);
                player->Y(absY);
                player->ladja_x = absX;
                player->ladja_y = absY;
            }
        }
        else if(type == 0 && desttype != 0){
            player->X(absX);
            player->Y(absY);
            player->ladja_x = x;
            player->ladja_y = y;
        }
        else if(type == 0 && desttype == 0){
            player->X(absX);
            player->Y(absY);
            player->ladja_x = absX;
            player->ladja_y = absY;
        }
        else{
            player->X(absX);
            player->Y(absY);
        }
    }
}