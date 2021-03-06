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

    int difficulty;

    bool checkBounds(int, int);
    void splitSelector(std::string, char&, int&, char&, int&);
    std::vector<Collision> listEntites();
    int checkColision();
public:
    Player* getPlayer() {return player;};
    Map* getLevel() {return level;};
    int getDiff() {return difficulty;};
    std::vector<Enemy*> getEnemies(){ return enemies;};
    std::vector<Trash*> getTrash(){ return trash;};
    std::vector<Animal*> getAnimals(){ return animals;};
    std::vector<Zaveznik*> getZavezniki(){ return zavezniki;};
    void setState(Player *_p, Map *_level, std::vector<Enemy*> _enemies, std::vector<Trash*> _trash, std::vector<Animal*> _animals, std::vector<Zaveznik*> _zavezniki, int _difficulty);
    Entities(int, int, int, int, int, Map*, SDL_Renderer*);
    void move(int, int);
    int update();
    std::vector<Collision> findCollisions();
    void render(SDL_Renderer*);
};

#endif // ENTITIES_H
