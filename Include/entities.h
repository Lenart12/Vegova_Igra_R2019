#if !defined(ENTITIES_H)
#define ENTITIES_H

#include <actors.h>
#include <map.h>

#include <string>
#include <vector>

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

    bool checkBounds(int, int);
    void checkColision();
public:
    Entities(int, int, int, Map*, SDL_Renderer*);
    void move(std::string, int, int);
    void update(Map*);
    void render(SDL_Renderer*);
};

#endif // ENTITIES_H
