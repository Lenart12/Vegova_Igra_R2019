#include <conf.h>

#include <SDL2/SDL.h>
#include <fstream>
#include <string>
#include <iostream>
#include <map>

std::map<std::string, int> loadCSV(){
    std::map<std::string, int> mapa;

    std::ifstream csv("config.csv");
    for(std::string line; getline(csv, line); ){
        int mid = line.find(',');
        std::string key = line.substr(0, mid),
                    value = line.erase(0, mid + 1);
        int iValue = std::atoi(value.c_str());
        mapa[key] = iValue;
    }

    return mapa;
}

Conf::Conf(){
    title = "Izbrisi plastiko";

    auto csv = loadCSV();

    gameFps = csv["gameFps"];
    tileX = csv["tileX"];
    tileY = csv["tileY"];
    tileCntX = csv["tileCntX"];
    tileCntY = csv["tileCntY"];
    if(csv["xpos"] == -1)
        xpos = SDL_WINDOWPOS_CENTERED;
    else
        xpos = csv["xpos"];
    if(csv["ypos"] == -1)
        ypos = SDL_WINDOWPOS_CENTERED;
    else
        ypos = csv["ypos"];
    width = tileX * tileCntX;
    height = tileY * tileCntY;
    fullscreen = csv["fullscreen"];
    flags = csv["flags"];
    enemyCnt = csv["enemyCnt"];
    trashCnt = csv["trashCnt"];
    animalCnt = csv["animalCnt"];
    zaveznikCnt = csv["zaveznikCnt"];
    mapGenPasses = csv["mapGenPasses"];
    fog = csv["fog"];
    fogDist = csv["fogDist"];
    gameTime = csv["gameTime"];
}