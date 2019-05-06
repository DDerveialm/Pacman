#include "game.h"
#include "inky.h"

Inky::Inky(Game *p) : Ghost(p, 3)
{
    init();
}

void Inky::init()
{
    x = 19;
    y = 13;
    t = 0;
    birth = 10;
    fri_flag = 0;
    const_ti = time_interval;
}

void Inky::set_des()
{
    if (fri_flag == 0 && game -> Mode() != 3) {
        des_x = 2 * (game -> c[0] -> X()) - game -> c[1] -> X();
        des_y = 2 * (game -> c[0] -> Y()) - game -> c[1] -> Y();
        if (game -> c[0] -> Dir() == 0) des_y -= 4;
        else if (game -> c[0] -> Dir() == 1) des_x += 4;
        else if (game -> c[0] -> Dir() == 2) des_y += 4;
        else if (game -> c[0] -> Dir() == 3) des_x -= 4;
        for (int d = 0; ; ++d) {
            int j;
            for (int i = 0; i <= d; ++i) {
                j = d - i;
                if (des_x + i >= 0 && des_x + i < WIDTH && des_y + j >= 0 && des_y + j < LENGTH && map[des_x + i][des_y + j] == 0) {
                    des_x += i;
                    des_y += j;
                    return ;
                }
                if (des_x + i >= 0 && des_x + i < WIDTH && des_y - j >= 0 && des_y - j < LENGTH && map[des_x + i][des_y - j] == 0) {
                    des_x += i;
                    des_y -= j;
                    return ;
                }
                if (des_x - i >= 0 && des_x - i < WIDTH && des_y + j >= 0 && des_y + j < LENGTH && map[des_x - i][des_y + j] == 0) {
                    des_x -= i;
                    des_y += j;
                    return ;
                }
                if (des_x - i >= 0 && des_x - i < WIDTH && des_y - j >= 0 && des_y - j < LENGTH &&map[des_x - i][des_y - j] == 0) {
                    des_x -= i;
                    des_y -= j;
                    return ;
                }
            }
        }
    } else if (fri_flag == 4) fri_flag = 3;
    else if (fri_flag == 3) fri_flag = 2;
    else if (fri_flag == 2) {
        if (x == 19 && y == 13) {
            fri_flag = 0;
        } else {
            des_x = 19;
            des_y = 13;
        }
    } else {
        des_x = 31;
        des_y = 20;
    }
}
