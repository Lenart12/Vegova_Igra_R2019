#if !defined(REPLAY_H)
#define REPLAY_H

#include <map.h>
#include <entities.h>

#include <fstream>
#include <iostream>
#include <vector>

struct Result{
    char name[15];
    int score;
};

class Input{
public:
    static std::string textInput;
};

namespace Replay{

    template<class T>
    void saveVector(std::vector<T> vector, std::ofstream *out){
        size_t size = vector.size();
        out->write((char*)&size, sizeof(size));
        out->write((char*)&vector[0], size * sizeof(T));
    }

    template<class T>
    std::vector<T> loadVector(std::ifstream *in){
        size_t size;
        in->read((char*)&size, sizeof(size));
        std::vector<T> vec(size);
        in->read((char*)&vec[0], size * sizeof(T));
        return vec;
    }

	void savePlayer(std::ofstream *out, Player* player);
	Player* loadPlayer(std::ifstream* in);
    void saveEntities(std::ofstream *out, Entities *_entities);
    Entities* loadEntites(std::ifstream *in, Entities *_entities, SDL_Renderer *renderer);
    void saveMap(std::ofstream *out, Map *_level);
    Map* loadMap(std::ifstream *in, SDL_Renderer *renderer);

    void saveResult(Result);
    std::vector<Result> loadResult(int limit);
}

#endif // REPLAY_H
