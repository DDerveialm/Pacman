#ifndef CLYDE_H
#define CLYDE_H

#include "ghost.h"

class Clyde : public Ghost
{
public:
    Clyde(Game *);
    void init();
    void set_des();

private:
    int clyde_flag = 0;
};

#endif // CLYDE_H
