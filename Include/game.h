#ifndef GAME_H
#define GAME_H

#include <iostream>

class BaseActor{
private:
    double health;
    int pos_x;
    int pos_y;
    int orientation;
public:
    virtual void setHealth(int);
    virtual void setX(int);
    virtual void setY(int);
    virtual void setOrientation(int);
    virtual double getHealth();
    virtual int getX();
    virtual int getY();
    virtual int getOrientation();
};

#endif