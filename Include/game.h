#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game
{
private:
    bool running;
    int cnt;
    SDL_Window *window;
    SDL_Renderer *renderer;
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvent();
    void update();
    void render();
    void clean();

    void setRunning(bool);
    void setCnt(int);
    bool getRunning();
    int getCnt();
};

class BaseActor{
private:
    double health;
    int pos_x;
    int pos_y;
    int orientation;
public:
    virtual void setHealth(int);
    virtual void setX(int);
    virtual void setY(int);
    virtual void setOrientation(int);
    virtual double getHealth();
    virtual int getX();
    virtual int getY();
    virtual int getOrientation();
};

#endif