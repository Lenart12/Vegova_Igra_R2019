#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <list>
#include <conf.h>

class Texture{
public:
    static void loadTextures(std::list<SDL_Texture*> &texture, const char*, SDL_Renderer*);
};

class Map{
private:
    int neighbours();
    int seed();
    int pass();
protected:
    std::list< std::list<int> > tiles;
};

class BaseActor : public Texture{
protected:
    double health;
    int pos_x;
    int pos_y;
    int orientation;
public:
    virtual void Health(int);
    virtual void X(int);
    virtual void Y(int);
    virtual void Orientation(int);

    virtual double Health();
    virtual int X();
    virtual int Y();
    virtual int Orientation();
};

class Player : public BaseActor{
private:
    bool onSea;
public:
    static std::list<SDL_Texture*> texture;
    void OnSea(bool);
    bool OnSea();
};

class Enemy : public BaseActor{
public:
    static std::list<SDL_Texture*> texture;

};

class Trash : public BaseActor{
public:
    static std::list<SDL_Texture*> texture;
};

class Animal : public BaseActor{
public:
    static std::list<SDL_Texture*> texture;
};

class Game
{
private:
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;

    Map *level;

    Player *player;
    std::list<Enemy*> enemies;
    std::list<Trash*> trash;
    std::list<Animal*> animals;

    Conf *conf;


public:
    static std::list<SDL_Texture*> worldTexture;
    
    Game();
    ~Game();

    void init();

    void handleEvent();
    void update();
    void render();
    void clean();

    void initTextures();
    void generateMap();

    void Running(bool);
    bool Running();
};

#endif