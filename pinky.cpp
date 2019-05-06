#include "game.h"
#include "pinky.h"

Pinky::Pinky(Game *p) : Ghost(p, 2)
{
    init();
}

void Pinky::init()
{
    x = 21;
    y = 10;
    t = 0;
    birth = 5;
    fri_flag = 0;
    const_ti = time_interval;
}

void Pinky::set_des()
{
    if (fri_flag == 0 && game -> Mode() != 3) {
        des_x = game -> c[0] -> X();
        des_y = game -> c[0] -> Y();
        if (game -> c[0] -> Dir() == 0) {
            if (map[des_x][des_y - 1] == 0) --des_y;
            if (map[des_x][des_y - 1] == 0) --des_y;
        }
        else if (game -> c[0] -> Dir() == 1) {
            if (map[des_x + 1][des_y] == 0) ++des_x;
            if (map[des_x + 1][des_y] == 0) ++des_x;
        }
        else if (game -> c[0] -> Dir() == 2) {
            if (map[des_x][des_y + 1] == 0) ++des_y;
            if (map[des_x][des_y + 1] == 0) ++des_y;
        }
        else if (game -> c[0] -> Dir() == 3) {
            if (map[des_x - 1][des_y] == 0) --des_x;
            if (map[des_x - 1][des_y] == 0) --des_x;
        }
    } else if (fri_flag == 4) fri_flag = 3;
    else if (fri_flag == 3) fri_flag = 2;
    else if (fri_flag == 2) {
        if (x == 21 && y == 10) {
            fri_flag = 0;
        } else {
            des_x = 21;
            des_y = 10;
        }
    } else {
        des_x = 1;
        des_y = 1;
    }
}
