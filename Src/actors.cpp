#include <actors.h>
#include <conf.h>

#include <SDL2/SDL.h>

void BaseActor::Health(int _health){ this->health = _health; }
void BaseActor::X(int _pos_x) { this->pos_x = _pos_x; }
void BaseActor::Y(int _pos_y) { this->pos_y = _pos_y; }
double BaseActor::Health(){ return this->health; }
int BaseActor::X(){ return this->pos_x; }
int BaseActor::Y(){ return this->pos_y; }

BaseActor::BaseActor(int startX, int startY){
    pos_x = startX;
    pos_y = startY;
}

Texture Player::texture;

void Player::render(SDL_Renderer *renderer, int txtIndex){
    Conf conf;
    SDL_Rect Drect;
    Drect.x = pos_x * conf.tileX;
    Drect.y = pos_y * conf.tileY;
    Drect.w = conf.tileX;
    Drect.h = conf.tileY;
    SDL_Texture *tex = Player::texture.getTexture(txtIndex);
    SDL_RenderCopy(renderer,
                    tex,
                    NULL, &Drect);
}