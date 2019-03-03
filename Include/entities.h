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

    Player *player;
    std::vector<Enemy*> enemies;
    std::vector<Trash*> trash;
    std::vector<Animal*> animals;

    Map *level;

    Texture fog;

    bool checkBounds(int, int);
    void splitSelector(std::string, char&, int&, char&, int&);
    std::vector<Collision> listEntites();
    void checkColision();
public:
    Entities(int, int, int, Map*, SDL_Renderer*);
    void move(std::string, int, int);
    void update();
    std::vector<Collision> findCollisions();
    void render(SDL_Renderer*);
};

#endif // ENTITIES_H
