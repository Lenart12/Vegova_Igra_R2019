#include <replay.h>
#include <algorithm>

std::string Input::textInput = "";


void Replay::savePlayer(std::ofstream* out, Player* player)
{
	out->write((char*)&(player->pos_x), sizeof(int));
	out->write((char*)&(player->pos_y), sizeof(int));
	out->write((char*)&(player->ladja_x), sizeof(int));
	out->write((char*)&(player->ladja_y), sizeof(int));
	out->write((char*)&(player->textureIndex), sizeof(int));
}

Player* Replay::loadPlayer(std::ifstream* in)
{
	Player* p = new Player();
	in->read((char*)&(p->pos_x), sizeof(int));
	in->read((char*)&(p->pos_y), sizeof(int));
	in->read((char*)&(p->ladja_x), sizeof(int));
	in->read((char*)&(p->ladja_y), sizeof(int));
	in->read((char*)&(p->textureIndex), sizeof(int));
	return p;
}

void Replay::saveEntities(std::ofstream *out, Entities *_entities){
    Player *p = _entities->getPlayer();
    std::vector<Enemy*> enemies = _entities->getEnemies();
    std::vector<Trash*> trash = _entities->getTrash();
    std::vector<Animal*> animals = _entities->getAnimals();
    std::vector<Zaveznik*> zavezniki = _entities->getZavezniki();
    Map *level = _entities->getLevel();
    int dif = _entities->getDiff();

    saveMap(out, level);

    out->write((char*)p, sizeof(Player));
    out->write((char*)&dif, sizeof(dif));
    
    size_t size = enemies.size();
    out->write((char*)&size, sizeof(size));
    for(int i = 0; i < size; i++){
        Enemy t = *enemies.at(i);
        out->write((char*)&t, sizeof(Enemy));
    }
    
    size = trash.size();
    out->write((char*)&size, sizeof(size));
    for(int i = 0; i < size; i++){
        Trash t = *trash.at(i);
        out->write((char*)&t, sizeof(Trash));
    }
    
    size = animals.size();
    out->write((char*)&size, sizeof(size));
    for(int i = 0; i < size; i++){
        Animal t = *animals.at(i);
        out->write((char*)&t, sizeof(Animal));
    }
    
    size = zavezniki.size();
    out->write((char*)&size, sizeof(size));
    for(int i = 0; i < size; i++){
        Zaveznik t = *zavezniki.at(i);
        out->write((char*)&t, sizeof(Zaveznik));
    }

}

Entities* Replay::loadEntites(std::ifstream *in, Entities *_entities, SDL_Renderer *renderer){
    Player *p = new Player();
    std::vector<Enemy*> enemies;
    std::vector<Trash*> trash;
    std::vector<Animal*> animals;
    std::vector<Zaveznik*> zavezniki;
    int dif;

    Map *level = loadMap(in, renderer);
    
    in->read((char*)p, sizeof(Player));
    in->read((char*)&dif, sizeof(dif));

    size_t size;

    in->read((char*)&size, sizeof(size));
    for(int i = 0; i < size; i++){
        Enemy *t = new Enemy;
        in->read((char*)t, sizeof(*t));
        enemies.push_back(t);
    }

    in->read((char*)&size, sizeof(size));
    for(int i = 0; i < size; i++){
        Trash *t = new Trash;
        in->read((char*)t, sizeof(*t));
        trash.push_back(t);
    }

    in->read((char*)&size, sizeof(size));
    for(int i = 0; i < size; i++){
        Animal *t = new Animal;
        in->read((char*)t, sizeof(*t));
        animals.push_back(t);
    }

    in->read((char*)&size, sizeof(size));
    for(int i = 0; i < size; i++){
        Zaveznik *t = new Zaveznik;
        in->read((char*)t, sizeof(*t));
        zavezniki.push_back(t);
    }

    _entities->setState(p, level, enemies, trash, animals, zavezniki, dif);
    return _entities;
}
void Replay::saveMap(std::ofstream *out, Map *_level){
    int w = _level->W();
    int h = _level->H();

    out->write((char*)&w, sizeof(w));
    out->write((char*)&h, sizeof(w));

    std::vector< std::vector<int> > tiles = _level->Tiles();

    size_t size = tiles.size();
    out->write((char*)&size, sizeof(size));

    for(std::vector<int> i : tiles){
        saveVector<int>(i, out);
    }
}
Map* Replay::loadMap(std::ifstream *in, SDL_Renderer *renderer){
    int w, h;

    in->read((char*)&w, sizeof(w));
    in->read((char*)&h, sizeof(h));

    std::vector< std::vector<int> > tiles;

    size_t size;
    in->read((char*)&size, sizeof(size));

    for(size_t i = 0; i < size; i++){
        tiles.push_back(loadVector<int>(in));
    }

    return new Map(w, h, tiles, renderer);
}

void Replay::saveResult(Result r){
    std::vector<Result> vec = loadResult(-1);
    vec.push_back(r);
    std::sort(vec.begin(), vec.end(), [](Result r1, Result r2) -> bool {return r1.score > r2.score;});
    std::ofstream out("Saves/tmpResults.bin", std::ios::app | std::ios::binary);
    if(out.is_open()){
        for(Result r : vec){
            out.write((char*)&r, sizeof(r));
        }
    }
	out.close();
    remove("Saves/results.bin");
	if (rename("Saves/tmpResults.bin", "Saves/results.bin") != 0) {
		std::cout << "Can't rename file\n";
	}
}
std::vector<Result> Replay::loadResult(int limit){
    Result r;
    std::vector<Result> vec;
    std::ifstream in("Saves/results.bin", std::ios::binary);
    int i = limit;
    if(in.is_open()){
        while((i-- >= 0 || limit == -1) && in.read((char*)&r, sizeof(r))){
            vec.push_back(r);
        }
        in.close();
    }
    return vec;
}