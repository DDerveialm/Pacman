#include "game.h"
#include "clyde.h"

Clyde::Clyde(Game *p) : Ghost(p, 4)
{
    init();
}

void Clyde::init()
{
    x = 21;
    y = 13;
    t = 0;
    birth = 16;
    fri_flag = 0;
    const_ti = time_interval;
}

void Clyde::set_des()
{
    des_x = game -> c[0] -> X();
    des_y = game -> c[0] -> Y();
    if (fri_flag) clyde_flag = 0;
    if (fri_flag == 0 && game -> Mode() != 3) {
        int dis = 8 - game -> Level();
        if (clyde_flag == 0) {
            if (BFS_best_path() <= dis)
                clyde_flag = 3;
            if (direction == 0) {
                des_x = x;
                des_y = y - 1;
            } else if (direction == 1) {
                des_x = x + 1;
                des_y = y;
            } else if (direction == 2) {
                des_x = x;
                des_y = y + 1;
            } else if (direction == 3) {
                des_x = x - 1;
                des_y = y;
            }
        }
        if (clyde_flag == 3) {
            if (x == 1 && y == 18) clyde_flag = 2;
            else {
                des_x = 1;
                des_y = 18;
            }
        }
        if (clyde_flag == 2) {
            if (x == 7 && y == 20) clyde_flag = 1;
            else {
                des_x = 7;
                des_y = 20;
            }
        }
        if (clyde_flag == 1) {
            if (x == 7 && y == 15) clyde_flag = 0;
            else {
                des_x = 7;
                des_y = 15;
            }
        }
    } else if (fri_flag == 4) fri_flag = 3;
    else if (fri_flag == 3) fri_flag = 2;
    else if (fri_flag == 2) {
        if (x == 21 && y == 13) {
            fri_flag = 0;
        } else {
            des_x = 21;
            des_y = 13;
        }
    } else {
        des_x = 1;
        des_y = 20;
    }
}
