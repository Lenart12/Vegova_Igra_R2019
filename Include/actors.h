#if !defined(ACTORS_H)
#define ACTORS_H

#include <texture.h>

class BaseActor{
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
    static Texture texture;
public:
    void OnSea(bool);
    bool OnSea();
};

class Enemy : public BaseActor{
    static Texture texture;

};

class Trash : public BaseActor{
    static Texture texture;
};

class Animal : public BaseActor{
    static Texture texture;
};

#endif // ACTORS_H