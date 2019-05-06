#ifndef DEVIL_H
#define DEVIL_H

#include "ghost.h"

class Devil : public Ghost
{
public:
    Devil(Game *);
    void init();
    void set_des();
    int BFS_best_path();
};

#endif // DEVIL_H
