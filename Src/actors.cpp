#include <actors.h>
#include <conf.h>

#include <SDL2/SDL.h>

void BaseActor::X(int _pos_x) {
    if(textureIndex % 2 == 0 &&  _pos_x < pos_x)
        textureIndex++;
    else if(textureIndex % 2 == 1 && _pos_x > pos_x){
        textureIndex--;
    }
    this->pos_x = _pos_x;
}
void BaseActor::Y(int _pos_y) { this->pos_y = _pos_y; }
void BaseActor::TextureIndex(int _textureIndex) { this->textureIndex = _textureIndex; }
int BaseActor::X(){ return this->pos_x; }
int BaseActor::Y(){ return this->pos_y; }
int BaseActor::TextureIndex(){ return this->textureIndex; }

BaseActor::BaseActor(int startX, int startY){
    textureIndex = 0;
    pos_x = startX;
    pos_y = startY;
}

void Player::update(Map *level) {
    int type = level->Type(pos_x, pos_y);
    if(type == 0 && textureIndex < 2)
        textureIndex += 2;
    else if(type != 0 && textureIndex > 1)
        textureIndex -= 2;
}

void Enemy::update(Map *level) {
    if(rand() % 100 < 20){
        int x, y;
        level->randomTile(pos_x, pos_y, x, y);
        X(x);
        Y(y);
    }
}

void Trash::update(Map *level) {
    if(rand() % 100 < 20){
        int x, y;
        level->randomTile(pos_x, pos_y, x, y);
        X(x);
        Y(y);
    }
}

void Animal::update(Map *level) { 
    if(rand() % 100 < 20){
        int x, y;
        level->randomTile(pos_x, pos_y, x, y);
        X(x);
        Y(y);
    }
}

void Zaveznik::update(Map *level) { 
    if(rand() % 100 < 20){
        int x, y;
        int type = level->Type(pos_x, pos_y);
        level->randomTile(pos_x, pos_y, x, y);
        X(x);
        Y(y);
        if(type == 0 && textureIndex < 2)
            textureIndex += 2;
        else if(type != 0 && textureIndex > 1)
            textureIndex -= 2;
    }
}