#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include <vector>

#include <conf.h>
#include <map.h>
class Menu;
#include <entities.h>


class Game
{
private:
    bool running;
    int dificulty;
    SDL_Window *window;
    SDL_Renderer *renderer;

    Map *level;

    Menu *menu;

    Entities *entities;

    Conf *conf;

    int hiscore;

public:
    static std::vector<SDL_Texture*> worldTexture;
    
    Game();
    ~Game();

    void init();
    void newGame();

    void handleEvent();
    void update();
    void render();
    void clean();

    void Running(bool);
    bool Running();

    void setMenu(Menu*);
    Menu* getMenu();
};

#endif