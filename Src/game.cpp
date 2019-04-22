#include <game.h>
#include <menu.h>

#include <iostream>
#include <fstream>
#include <SDL2/SDL_image.h>

Game::Game() { 
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
}

Game::~Game(){
    TTF_Quit();
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

                if(conf->fullscreen){
                    SDL_SetWindowFullscreen(window, conf->flags);
                    SDL_MaximizeWindow(window);
                }
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
        level = NULL;
        entities = NULL;
        inGame = false;
        menu = new Menu();
    }
}


void Game::newGame(){
    remove("Saves/lastReplay.bin");
    timer = SDL_GetTicks();
    score = 0;
    inGame = true;
    dificulty = 0;
    newLevel();
}

void Game::newLevel(){
    if(level != NULL) delete level;
    if(entities != NULL) delete entities;
    level = new Map(conf->tileCntX, conf->tileCntY, conf->mapGenPasses, renderer);
    entities = new Entities(conf->enemyCnt,
                            conf->trashCnt,
                            conf->animalCnt,
                            conf->zaveznikCnt,
                            dificulty,
                            level, renderer);
}

void Game::handleEvent(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
                running = false;
        }
        else if(event.type == SDL_KEYDOWN && menu == NULL){
            switch(event.key.keysym.sym){
                case SDLK_w: entities->move(0, -1); break;
                case SDLK_a: entities->move(-1, 0); break;
                case SDLK_s: entities->move(0, 1); break;
                case SDLK_d: entities->move(1, 0); break;
                
                
                case SDLK_ESCAPE: menu = new Menu();
                    dificulty = 0;
                    break;
            }
        }
    }
}

size_t strlcpy(char *dst, const char *src, size_t size)
{
    size_t len = 0;
    while(size > 1 && *src)
    {
        *dst++ = *src++;
        size--;
        len++;
    }
    if(size > 0)
        *dst = 0;
    return len + strlen(src);    
}

void Game::update(){
    if(menu == NULL){
        bool over = SDL_GetTicks() - timer > conf->gameTime * 1000;
        int ret = entities->update();
        std::ofstream outSave("Saves/lastReplay.bin", std::ios::app | std::ios::binary);
        Replay::saveEntities(&outSave, entities);
        outSave.close();
        if(ret == -10000 || over){
            inGame = false;
            menu = new Menu();
        }
        else if(ret == -10001){
            dificulty += 2;
            delete entities;
            delete level;
            level = new Map(conf->tileCntX, conf->tileCntY, conf->mapGenPasses, renderer);
            entities = new Entities(conf->enemyCnt,
                            conf->trashCnt,
                            conf->animalCnt,
                            conf->zaveznikCnt,
                            dificulty,
                            level, renderer);
        }
        else{
            score += ret;
        }
    }
    else{
        GameState state = STATE_NOTHING;
        if(inGame)
            state = STATE_ACTIVE;
        else if(!inGame && level != NULL){
            delete level;
            delete entities;
            level = NULL;
            entities = NULL;
            state = STATE_GAME_OVER;
        }
        switch(menu->update(state, renderer)){
            case MENU_INPUT_NAME:{
                inGame = false;
                menu = new Menu();
                break;
            }
            case MENU_NEW_GAME:
                inGame = true;
                delete menu;
                menu = NULL;
                newGame();
                break;
            case MENU_SAVE_GAME: {
                remove("Saves/tmp.map");

                std::ofstream outSave("Saves/tmp.map", std::ios::app | std::ios::binary);
                Replay::saveEntities(&outSave, entities);
                outSave.close();

                menu->message = "Igra shranjena";

                break;
            }
            case MENU_LOAD_GAME: {
                timer = SDL_GetTicks();
                inGame = true;
                delete level;
                delete entities;
                entities = new Entities(0, 0, 0, 0, 0, NULL, renderer);

                std::ifstream in("Saves/tmp.map", std::ios::binary);
                entities = Replay::loadEntites(&in, entities, renderer);
                level = entities->getLevel();
                in.close();

                delete menu;
                menu = NULL;

                break;
            }
            case MENU_RESUME: {
                inGame = true;
                delete menu;
                menu = NULL;
                break;
            }
            case MENU_QUIT: {
                running = false;
                break;
            }
            case MENU_NOTHING: {
                break;
            }
            case MENU_SAVE_RESULT: {
                inGame = false;
                Result r;
                strlcpy(r.name, Input::textInput.c_str(), 15);
                r.score = score;
                Replay::saveResult(r);
                break;
            }
            case MENU_WATCH_REPLAY:{
                static Conf conf;
                const int FPS = conf.gameFps;
                const int frameDelay = 1000 / FPS;

                inGame = true;

                Uint32 frameStart;
                int frameTime;
                std::ifstream in("Saves/lastReplay.bin", std::ios::binary);
                if(in.is_open()){
                    while(!in.eof()){
                        frameStart = SDL_GetTicks();

                        delete level;
                        delete entities;
                        entities = new Entities(0, 0, 0, 0, 0, NULL, renderer);
                        
                        entities = Replay::loadEntites(&in, entities, renderer);
                        level = entities->getLevel();
                        SDL_RenderClear(renderer);
                        level->render(renderer);
                        entities->render(renderer);
                        SDL_RenderPresent(renderer);


                        frameTime = SDL_GetTicks() - frameStart;

                        if(frameDelay > frameTime){
                            SDL_Delay(frameDelay - frameTime);
                        }
                    }
                }
            }
        }
    }
}


void Game::render(){
    SDL_RenderClear(renderer);
    if(menu == NULL){
        level->render(renderer);
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
