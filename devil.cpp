#include "game.h"
#include "devil.h"

Devil::Devil(Game *p) : Ghost(p, 5)
{
    init();
}

void Devil::init()
{
    x = 20;
    y = 12;
    t = 0;
    birth = 25;
    const_ti = time_interval;
}

void Devil::set_des()
{
    if (fri_flag == 0 && game -> Mode() != 3) {
        if (game -> Level() != 3) {
            int vector_x = 0, vector_y = 0;
            for (int i = 1; i <= 4; ++i) {
                vector_x += game -> c[i] -> X();
                vector_y += game -> c[i] -> Y();
            }
            vector_x /= 4;
            vector_y /= 4;
            des_x = 2 * (game -> c[0] -> X()) - vector_x;
            des_y = 2 * (game -> c[0] -> Y()) - vector_y;
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
        } else {
            if (x > 18 && x < 22 && y >= 9 && y < 14) {
                des_x = 20;
                des_y = 8;
            } else {
                des_x = game -> c[0] -> X();
                des_y = game -> c[0] -> Y();
            }
        }
    }  else if (fri_flag == 4) fri_flag = 3;
    else if (fri_flag == 3) fri_flag = 2;
    else if (fri_flag == 2) {
        if (x == 20 && y == 12) {
            fri_flag = 0;
        } else {
            des_x = 20;
            des_y = 12;
        }
    } else {
        des_x = 20;
        des_y = 8;
    }
}


int Devil::BFS_best_path()
{
    if (game -> Level() == 2) {
        if (x < 0 || x >= WIDTH || y < 0 || y >= LENGTH\
                || des_x < 0 || des_x >= WIDTH || des_y < 0 || des_y >= LENGTH\
                || (map[x][y] != 0 && map[x][y] != 3) || map[des_x][des_y] != 0) return 0;
        map[x][y] = -1;
        for (int n = 1; map[des_x][des_y] == 0; ++n) {
            int flag = 0;
            for (int i = 0; i < WIDTH; ++i)
                for (int j = 0; j < LENGTH; ++j)
                    if (map[i][j] == -1 * n) {
                        if (map[i + 1][j] == 0) {
                            map[i + 1][j] = -1 * (n + 1);
                            flag = 1;
                        }
                        if (map[i - 1][j] == 0) {
                            map[i - 1][j] = -1 * (n + 1);
                            flag = 1;
                        }
                        if (map[i][j + 1] == 0) {
                            map[i][j + 1] = -1 * (n + 1);
                            flag = 1;
                        }
                        if (map[i][j - 1] == 0) {
                            map[i][j - 1] = -1 * (n + 1);
                            flag = 1;
                        }
                        if (i == 4 && j == 1)
                            if (map[19][21] == 3) map[19][21] = -1 * (n + 1);
                        if (i == 19 && j == 20)
                            if (map[4][0] == 3) map[4][0] = -1 * (n + 1);
                    }
            if (flag == 0) {
                for (int i = 0; i < WIDTH; ++i)
                    for (int j = 0; j < LENGTH; ++j)
                        if (map[i][j] < 0) map[i][j] = 0;
                return 0;
            }
        }
        int temp_x = des_x;
        int temp_y = des_y;
        int distance = -1 * (map[des_x][des_y] + 1);
        while (temp_x != x || temp_y != y) {
            if (map[temp_x][temp_y] == -2) {
                if (temp_x == 4 && temp_y == 0) direction = 2;
                else if (temp_x == 19 && temp_y == 21) direction = 0;
                else if (map[temp_x + 1][temp_y] == -1) direction = 3;
                else if (map[temp_x - 1][temp_y] == -1) direction = 1;
                else if (map[temp_x][temp_y + 1] == -1) direction = 0;
                else if (map[temp_x][temp_y - 1] == -1) direction = 2;
            }
            if (temp_x == 4 && temp_y == 0) {
                temp_x = 19;
                temp_y = 20;
                continue;
            } else if (temp_x == 19 && temp_y == 21) {
                temp_x = 4;
                temp_y = 1;
                continue;
            }
            if (map[temp_x + 1][temp_y] == map[temp_x][temp_y] + 1) temp_x += 1;
            else if (map[temp_x - 1][temp_y] == map[temp_x][temp_y] + 1) temp_x -= 1;
            else if (map[temp_x][temp_y + 1] == map[temp_x][temp_y] + 1) temp_y += 1;
            else if (map[temp_x][temp_y - 1] == map[temp_x][temp_y] + 1) temp_y -= 1;
        }
        for (int i = 0; i < WIDTH; ++i)
            for (int j = 0; j < LENGTH; ++j)
                if (map[i][j] < 0) map[i][j] = 0;
        map[4][0] = 3;
        map[19][21] = 3;
        return distance;
    } else if (game -> Level() == 3) {
        if (Ghost::t % 2) {
            if (des_x < WIDTH && des_x > x) direction = 1;
            else if (des_x > 0 && des_x < x) direction = 3;
            else if (des_y < LENGTH && des_y > y) direction = 2;
            else if (des_y > 0 && des_y < y) direction = 0;
        } else {
            if (des_y < LENGTH && des_y > y) direction = 2;
            else if (des_y > 0 && des_y < y) direction = 0;
            else if (des_x < WIDTH && des_x > x) direction = 1;
            else if (des_x > 0 && des_x < x) direction = 3;
        }
    }
    return 0;
}
