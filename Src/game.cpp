#include <game.h>
#include <menu.h>

#include <iostream>
#include <SDL2/SDL_image.h>

Game::Game() { 
    IMG_Init(IMG_INIT_PNG);
}

Game::~Game(){
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::init(){
    conf = new Conf;

    if(conf->fullscreen){
        conf->flags |= SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(conf->title,
                                        conf->xpos,
                                        conf->ypos,
                                        conf->width,
                                        conf->height,
                                        conf->flags);

        if(window != NULL){
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                running = true;
            }
            else{
                std::cout << "Failed to create Renderer: " << SDL_GetError();
                running = false;
            }
        }
        else{
            std::cout << "Failed to create Window: " << SDL_GetError();
            running = false;
        }
    }
    else {
        std::cout << "Failed to init SDL: " << SDL_GetError();
        running = false;
    }

    if(running){
        hiscore = 0;
        level = new Map(conf->tileCntX,
                        conf->tileCntY,
                        conf->mapGenPasses,
                        renderer);
        menu = new Menu(hiscore);
    }
}


void Game::newGame(){
    level = new Map(conf->tileCntX, conf->tileCntY, conf->mapGenPasses, renderer);
    entities = new Entities(conf->enemyCnt, conf->trashCnt, conf->animalCnt, level, renderer);
}

void Game::handleEvent(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
                running = false;
        }
        else if(event.type == SDL_KEYDOWN && menu == NULL){
            switch(event.key.keysym.sym){
                case SDLK_w: entities->move("p", 0, -1); break;
                case SDLK_a: entities->move("p", -1, 0); break;
                case SDLK_s: entities->move("p", 0, 1); break;
                case SDLK_d: entities->move("p", 1, 0); break;

                case SDLK_ESCAPE: menu = new Menu(hiscore); break;
            }
        }
    }
}
void Game::update(){
    if(menu == NULL)
        entities->update();
    else
        menu->update(this);
    
}

void Game::render(){
    SDL_RenderClear(renderer);
    level->render(renderer);
    if(menu == NULL){
        entities->render(renderer);
    }
    else{
        menu->render(renderer);
    }
    SDL_RenderPresent(renderer);
}

void Game::Running(bool _running){ running = _running; }
bool Game::Running(){ return running; }
void Game::setMenu(Menu *_menu) { menu = _menu; }
Menu* Game::getMenu() { return menu; }