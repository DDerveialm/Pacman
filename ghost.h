#ifndef GHOST_H
#define GHOST_H

#include "char.h"

class Ghost : public Char
{
public:
    Ghost(Game *, int);
    int Flag();

protected:
    int des_x, des_y, t = 0, birth, const_ti;
    virtual void set_des() =0;
    virtual int BFS_best_path();

private slots:
    void move();

};

#endif // GHOST_H
