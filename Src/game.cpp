#include <game.h>

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

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        running = true;
    }
    else {
        running = false;
    }

    level = new Map(conf->tileCntX, conf->tileCntY, 0);

    level->worldTexture.loadTextures("Texture/morje.png", renderer);
    level->worldTexture.loadTextures("Texture/morje3.png", renderer);
    level->worldTexture.loadTextures("Texture/kopno.png", renderer);
    level->worldTexture.loadTextures("Texture/kopno3.png", renderer);
}

void Game::handleEvent(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
        case SDL_QUIT:
            running = false;
            break;
    
        default:
            break;
    }
}
void Game::update(){
}

void Game::render(){
    SDL_RenderClear(renderer);
    level->render(renderer,
                  conf->tileX,
                  conf->tileY);
    level->pass(1);
    SDL_Delay(200);
    SDL_RenderPresent(renderer);
}

void Game::Running(bool _running){
    running = _running;
}

bool Game::Running(){
    return running;
}