#include <actors.h>
#include <conf.h>

#include <SDL2/SDL.h>

void BaseActor::X(int _pos_x) { this->pos_x = _pos_x; }
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
    switch (type)
    {
        case 0:
            textureIndex = 2;
            break;
        default:
            textureIndex = 0;
            break;
    }
}

void Enemy::update(Map *level) {
    if(rand() % 100 < 20)
        level->randomTile(pos_x, pos_y, pos_x, pos_y);
}

void Trash::update(Map *level) {
    if(rand() % 100 < 20)
        level->randomTile(pos_x, pos_y, pos_x, pos_y);
}

void Animal::update(Map *level) { 
    if(rand() % 100 < 20)
        level->randomTile(pos_x, pos_y, pos_x, pos_y);
}