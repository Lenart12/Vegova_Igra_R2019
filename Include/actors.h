#if !defined(ACTORS_H)
#define ACTORS_H

#include <texture.h>
#include <map.h>

class BaseActor{
protected:
    int pos_x;
    int pos_y;
    int textureIndex;
public:
    BaseActor(int, int);

    virtual void X(int);
    virtual void Y(int);
    virtual void TextureIndex(int);

    virtual int X();
    virtual int Y();
    virtual int TextureIndex();

    virtual void update(Map*)=0;
};

class Player : public BaseActor{
public:
    int ladja_x;
    int ladja_y;
    Player(int startX, int startY) : BaseActor(startX, startY) { };
    virtual void update(Map*);
};

class Enemy : public BaseActor{
public:
    Enemy(int startX, int startY) : BaseActor(startX, startY) { };
    virtual void update(Map*);
};

class Trash : public BaseActor{
public:
    Trash(int startX, int startY) : BaseActor(startX, startY) { };
    virtual void update(Map*);
};

class Animal : public BaseActor{
public:
    Animal(int startX, int startY) : BaseActor(startX, startY) { };
    virtual void update(Map*);
};

class Zaveznik : public BaseActor{
public:
    Zaveznik(int startX, int startY) : BaseActor(startX, startY) { };
    virtual void update(Map*);
};

#endif // ACTORS_H