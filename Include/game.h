#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include <vector>
#include <fstream>

#include <conf.h>
#include <map.h>
class Menu;
#include <entities.h>
#include <replay.h>


class Game
{
private:
    bool running;
    bool inGame;
    int dificulty;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Uint32 timer;
    Map *level;

    Menu *menu;

    Entities *entities;

    Conf *conf;
    int score;

public:
    static std::vector<SDL_Texture*> worldTexture;

    Game();
    ~Game();

    void init();
    void newGame();
    void newLevel();

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