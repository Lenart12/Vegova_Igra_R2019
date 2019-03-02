#if !defined(ACTORS_H)
#define ACTORS_H

#include <texture.h>

class BaseActor{
protected:
    double health;
    int pos_x;
    int pos_y;
public:
    BaseActor(int, int);

    virtual void Health(int);
    virtual void X(int);
    virtual void Y(int);

    virtual double Health();
    virtual int X();
    virtual int Y();

    virtual void render(SDL_Renderer*, int)=0;
};

class Player : public BaseActor{
public:
    static Texture texture;
    Player(int startX, int startY) : BaseActor(startX, startY) { };
    void render(SDL_Renderer*, int);
};

class Enemy : public BaseActor{
private:
    static Texture texture;

};

class Trash : public BaseActor{
private:
    static Texture texture;
};

class Animal : public BaseActor{
private:
    static Texture texture;
};

#endif // ACTORS_H