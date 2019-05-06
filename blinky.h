#ifndef BLINKY_H
#define BLINKY_H

#include "ghost.h"

class Blinky : public Ghost
{
public:
    Blinky(Game *);
    void init();
    void set_des();
};

#endif // BLINKY_H
