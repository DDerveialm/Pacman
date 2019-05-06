#include "game.h"
#include "blinky.h"

Blinky::Blinky(Game *p) : Ghost(p, 1)
{
    init();
}

void Blinky::init()
{
    x = 19;
    y = 10;
    t = 0;
    birth = 2;
    fri_flag = 0;
    const_ti = time_interval;
}

void Blinky::set_des()
{
    if (fri_flag == 0 && game -> Mode() != 3) {
        des_x = game -> c[0] -> X();
        des_y = game -> c[0] -> Y();
    } else if (fri_flag == 4) fri_flag = 3;
    else if (fri_flag == 3) fri_flag = 2;
    else if (fri_flag == 2) {
        if (x == 19 && y == 10) {
            fri_flag = 0;
        } else {
            des_x = 19;
            des_y = 10;
        }
    } else {
        des_x = 31;
        des_y = 1;
    }
}
