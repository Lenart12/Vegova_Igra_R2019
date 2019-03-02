#ifndef _CONF_H
#define _CONF_H

class Conf{
public:
    int gameFps;

    int tileX,
        tileY,
        tileCntX,
        tileCntY;

    const char* title;

    int xpos,
        ypos,
        width,
        height;

    bool fullscreen;

    int flags;

    int enemyCnt,
        trashCnt,
        animalCnt;

    int mapGenPasses;

    Conf();
};

#endif