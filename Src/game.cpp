#include <game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture* playerTex;
SDL_Rect* srcR, destR;


Game::Game(){
    this->cnt = 0;
}
Game::~Game(){
    this->clean();
}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        this->window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        this->renderer = SDL_CreateRenderer(this->window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
        }
        this->running = true;
    }
    else {
        this->running = false;
    }

    SDL_Surface* tmp = IMG_Load("Texture/pahor.jpeg");
    playerTex = SDL_CreateTextureFromSurface(this->renderer, tmp);
    SDL_FreeSurface(tmp);
}
void Game::handleEvent(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
        case SDL_QUIT:
            this->running = false;
            break;
    
        default:
            break;
    }
}
void Game::update(){
    (this->cnt)++;
    destR.h = 280;
    destR.w = 160;
    destR.x = cnt;

    if(this->cnt > 1240){
        this->cnt = -250;
    }
}
void Game::render(){
    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, playerTex, NULL, &destR);
    SDL_RenderPresent(this->renderer);
}
void Game::clean(){
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
}
void Game::setRunning(bool _running){
    this->running = _running;
}
void Game::setCnt(int _cnt){
    this->cnt = _cnt;
}
bool Game::getRunning(){
    return this->running;
}
int Game::getCnt(){
    return this->cnt;
}

void BaseActor::setHealth(int _health){
    this->health = _health;
}
void BaseActor::setX(int _pos_x){
    this->pos_x = _pos_x;
}
void BaseActor::setY(int _pos_y){
    this->pos_y = _pos_y;
}
void BaseActor::setOrientation(int _orientation){
    this->orientation = _orientation;
}
double BaseActor::getHealth(){
    return this->health;
}
int BaseActor::getX(){
    return this->pos_x;
}
int BaseActor::getY(){
    return this->pos_y;
}
int BaseActor::getOrientation(){
    return this->orientation;
}