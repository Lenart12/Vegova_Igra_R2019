#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include <vector>

#include <conf.h>
#include <map.h>
#include <actors.h>


class Game
{
private:
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;

    Map *level;

    Player *player;
    std::vector<Enemy*> enemies;
    std::vector<Trash*> trash;
    std::vector<Animal*> animals;

    Conf *conf;


public:
    static std::vector<SDL_Texture*> worldTexture;
    
    Game();
    ~Game();

    void init();

    void handleEvent();
    void update();
    void render();
    void clean();

    void Running(bool);
    bool Running();
};

#endif