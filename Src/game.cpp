#include <game.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Game::Game() {   }

Game::~Game(){
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
}

void Game::init(){
    conf = new Conf;

    if(conf->fullscreen){
        conf->flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        this->window = SDL_CreateWindow(conf->title,
                                        conf->xpos,
                                        conf->ypos,
                                        conf->width,
                                        conf->height,
                                        conf->flags);

        this->renderer = SDL_CreateRenderer(this->window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
        }
        this->running = true;
    }
    else {
        this->running = false;
    }

    initTextures();
    generateMap();
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

}

void Game::render(){
    SDL_RenderPresent(this->renderer);
}

void Game::initTextures(){
    Player::loadTextures(Player::texture , "Texture/ladja.png", renderer);
    Player::loadTextures(Player::texture , "Texture/player.png", renderer);
    
    Enemy::loadTextures(Enemy::texture, "Texture/enemy.png", renderer);
    
    Trash::loadTextures(Trash::texture, "Texture/trash.png", renderer);

    Animal::loadTextures(Animal::texture, "Texture/animal.png", renderer);

    Texture::loadTextures(Game::worldTexture, "Texture/morje.png", renderer);
    Texture::loadTextures(Game::worldTexture, "Texture/kopno.png", renderer);
}
    
void Game::generateMap(){
    
}

void Game::Running(bool _running){
    this->running = _running;
}

bool Game::Running(){
    return this->running;
}


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

void Texture::loadTextures(std::list<SDL_Texture*> &texture, const char *textureLocation, SDL_Renderer *renderer){
    SDL_Texture *tmp = IMG_LoadTexture(renderer, textureLocation);
    texture.push_back(tmp);
}

void Player::OnSea(bool _onSea){
    onSea = _onSea;
}
bool Player::OnSea(){
    return onSea;
}