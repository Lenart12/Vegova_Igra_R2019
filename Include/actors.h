#if !defined(ACTORS_H)
#define ACTORS_H

#include <texture.h>
#include <map.h>

class BaseActor{
public:
    int textureIndex;
    int pos_x;
    int pos_y;
	BaseActor() { textureIndex = -1; pos_x = -1; pos_y = -1; };
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
    Player(int startX, int startY) : BaseActor(startX, startY) { ladja_x = -1; ladja_y = -1; };
	Player() : BaseActor() { ladja_x = -1; ladja_y = -1; };
    virtual void update(Map*);
};

class Enemy : public BaseActor{
public:
    Enemy(int startX, int startY) : BaseActor(startX, startY) { };
    Enemy() : BaseActor() { };
    virtual void update(Map*);
};

class Trash : public BaseActor{
public:
    Trash(int startX, int startY) : BaseActor(startX, startY) { };
    Trash() : BaseActor() { };
    virtual void update(Map*);
};

class Animal : public BaseActor{
public:
    Animal(int startX, int startY) : BaseActor(startX, startY) { };
    Animal() : BaseActor() { };
    virtual void update(Map*);
};

class Zaveznik : public BaseActor{
public:
    Zaveznik(int startX, int startY) : BaseActor(startX, startY) { };
    Zaveznik() : BaseActor() { };
    virtual void update(Map*);
};

#endif // ACTORS_H