#ifndef PINKY_H
#define PINKY_H

#include "ghost.h"

class Pinky : public Ghost
{
public:
    Pinky(Game *);
    void init();
    void set_des();
};

#endif // PINKY_H
