#ifndef PACMAN_H
#define PACMAN_H

#include "char.h"

class Pacman : public Char
{
public:
    Pacman(Game *ptr);

private slots:
    void move();
};

#endif // PACMAN_H
