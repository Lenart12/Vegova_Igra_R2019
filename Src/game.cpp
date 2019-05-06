#include <game.h>
#include <menu.h>

#include <iostream>
#include <fstream>
#include <SDL_image.h>

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

	std::ofstream outSave("Saves/lastReplay.bin", std::ios::app | std::ios::binary);
	int tmp = 0;
	outSave.write((char*)& tmp, sizeof(tmp));
	Replay::saveMap(&outSave, level);
	outSave.close();

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
                
                
                case SDLK_ESCAPE:
					menu = new Menu();
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
		int tmp = 1;
		Player* p = entities->getPlayer();
		outSave.write((char*)& tmp, sizeof(tmp));
		Replay::savePlayer(&outSave, p);
		outSave.close();

        if(ret == -10000 || over){
            inGame = false;
            menu = new Menu();
        }
        else if(ret == -10001){
            dificulty += 2;
			newLevel();
        }
        else{
            score += ret;
			if (ret != 0)
				std::cout << "SCORE: " << score << '\n';
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
                remove("Saves/save.bin");

                std::ofstream outSave("Saves/save.bin", std::ios::app | std::ios::binary);
                Replay::saveEntities(&outSave, entities);
                outSave.close();

                menu->message = "Igra shranjena";

                break;
            }
            case MENU_LOAD_GAME: {
                std::ifstream in("Saves/save.bin", std::ios::binary);
				if (in.good()) {
					timer = SDL_GetTicks();
					inGame = true;
					delete level;
					delete entities;
					entities = new Entities(0, 0, 0, 0, 0, NULL, renderer);

					entities = Replay::loadEntites(&in, entities, renderer);
					level = entities->getLevel();

					delete menu;
					menu = NULL;
				}
				else
					menu->message = "Nobena igra ni shranjena";
				in.close();
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

				delete entities;
				entities = NULL;
				delete level;
				level = NULL;

                break;
            }
            case MENU_WATCH_REPLAY:{
				inGame = false;
                static Conf conf;
                const int FPS = conf.gameFps;
                const int frameDelay = 1000 / FPS;

                Uint32 frameStart;
                int frameTime;

                std::ifstream in("Saves/lastReplay.bin", std::ios::binary);
				if (in.good()) {
					int tmp;
					Player* p = NULL;
					Texture playerTexture;

					playerTexture.loadTextures("Texture\\player1.png", renderer);
					playerTexture.loadTextures("Texture\\player2.png", renderer);
					playerTexture.loadTextures("Texture\\ladja1.png", renderer);
					playerTexture.loadTextures("Texture\\ladja2.png", renderer);

					SDL_Event event;
					bool exit = false;

					if (in.is_open()) {
						while (!in.eof()) {
							while (SDL_PollEvent(&event)) {
								if (event.type == SDL_QUIT) {
									running = false;
									exit = true;
								}
								else if (event.type == SDL_KEYDOWN) {
									switch (event.key.keysym.sym) {
									case SDLK_ESCAPE:
										exit = true;
										break;
									}
								}
							}
							if (exit)
								break;


							frameStart = SDL_GetTicks();

							in.read((char*)& tmp, sizeof(tmp));
							switch (tmp) {
							case 0:
								if (level != NULL)
									delete level;
								level = Replay::loadMap(&in, renderer);
								continue;
							case 1:
								if (p != NULL)
									delete p;
								p = Replay::loadPlayer(&in);
								break;
							default:
								menu->message = "Napaka";
								delete level;
								level = NULL;
								in.close();
								return;
							}
							if (p == NULL || level == NULL) {
								menu->message = "Napaka";
								if (level != NULL)
									delete level;
								if (p != NULL)
									delete p;
								level = NULL;
								in.close();
								return;
							}
							else {
								SDL_RenderClear(renderer);
								level->render(renderer);

								int pos_x, pos_y,
									textureIndex;

								pos_x = p->pos_x;
								pos_y = p->pos_y;
								textureIndex = p->textureIndex;
								playerTexture.renderTile(pos_x, pos_y, playerTexture.getTexture(textureIndex), renderer);
								if (p->ladja_x != pos_x || p->ladja_y != pos_y) {
									playerTexture.renderTile(p->ladja_x, p->ladja_y, playerTexture.getTexture(2), renderer);
								}

								SDL_RenderPresent(renderer);

								frameTime = SDL_GetTicks() - frameStart;

								if (frameDelay > frameTime) {
									SDL_Delay(frameDelay - frameTime);
								}
							}
						}
					}
					delete level;
					level = NULL;
				}
				else {
					menu->message = "Noben posnetek ni shranjen";
				}
				in.close();
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
