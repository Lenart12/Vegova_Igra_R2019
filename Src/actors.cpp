#include <actors.h>

#include <SDL2/SDL_image.h>

void BaseActor::Health(int _health){
    this->health = _health;
}
void BaseActor::X(int _pos_x){
    this->pos_x = _pos_x;
}
void BaseActor::Y(int _pos_y){
    this->pos_y = _pos_y;
}
void BaseActor::Orientation(int _orientation){
    this->orientation = _orientation;
}
double BaseActor::Health(){
    return this->health;
}
int BaseActor::X(){
    return this->pos_x;
}
int BaseActor::Y(){
    return this->pos_y;
}
int BaseActor::Orientation(){
    return this->orientation;
}

void Player::OnSea(bool _onSea){
    onSea = _onSea;
}
bool Player::OnSea(){
    return onSea;
}
