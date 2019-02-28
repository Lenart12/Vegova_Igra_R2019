#ifndef _CONF_H
#define _CONF_H

class Conf{
public:
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

    Conf();
};

#endif