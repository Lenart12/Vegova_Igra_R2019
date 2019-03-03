#if !defined(ENTITIES_H)
#define ENTITIES_H

#include <actors.h>
#include <map.h>

#include <string>
#include <vector>

class Collision{
public:
    Collision(std::string, int, int);
    std::string selector;
    int pos_x;
    int pos_y;
};

class Entities{
private:
    Texture playerTexture;
    Texture enemyTexture;
    Texture trashTexture;
    Texture animalTexture;
    Texture zaveznikTexture;

    Player *player;
    std::vector<Enemy*> enemies;
    std::vector<Trash*> trash;
    std::vector<Animal*> animals;
    std::vector<Zaveznik*> zavezniki;

    Map *level;

    Texture fog;

    bool checkBounds(int, int);
    void splitSelector(std::string, char&, int&, char&, int&);
    std::vector<Collision> listEntites();
    int checkColision();
public:
    Entities(int, int, int, int, Map*, SDL_Renderer*);
    void move(int, int);
    int update();
    std::vector<Collision> findCollisions();
    void render(SDL_Renderer*);
};

#endif // ENTITIES_H
