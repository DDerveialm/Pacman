#ifndef INKY_H
#define INKY_H

#include "ghost.h"

class Inky : public Ghost
{
public:
    Inky(Game *);
    void init();
    void set_des();
};

#endif // INKY_H
