#include "game.h"
#include "ghost.h"

Ghost::Ghost(Game *p, int t) :Char(p, t)
{
    map[20][9] = 0;

    connect(this, SIGNAL(pos_changed()), game, SLOT(check_pos()));
}

int Ghost::BFS_best_path()
{
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
}

void Ghost::move()
{
    if (game -> Mode() == -1) {
        move_timer -> setInterval(10);
        return ;
    }

    direction = -1;
    des_x = 0;
    des_y = 0;

    if (t <= birth + 10) {
        if (type == 1) {
            if (x == 19 && y == 10) ++x;
            else if (x == 20 && y == 10) ++y;
            else if (x == 20 && y == 11) --x;
            else if (x == 19 && y == 11) --y;
        } else if (type == 2) {
            if (x == 21 && y == 10) --x;
            else if (x == 20 && y == 10) ++y;
            else if (x == 20 && y == 11) ++x;
            else if (x == 21 && y == 11) --y;
        } else if (type == 3) {
            if (x == 19 && y == 13) ++x;
            else if (x == 20 && y == 13) --y;
            else if (x == 20 && y == 12) --x;
            else if (x == 19 && y == 12) ++y;
        } else if (type == 4) {
            if (x == 21 && y == 13) --x;
            else if (x == 20 && y == 13) --y;
            else if (x == 20 && y == 12) ++x;
            else if (x == 21 && y == 12) ++y;
        } else if (type == 5) {
            if (x == 19 && y == 11) {
                x += 1;
                y += 2;
            } else if (x == 20 && y == 13) {
                x += 1;
                y -= 2;
            } else if (x == 21 && y == 11) {
                x -= 1;
                y += 1;
            } else if (x == 20 && y == 12) {
                x -= 1;
                y -= 1;
            }
        }
    } else {
        set_des();
        BFS_best_path();

        int transport_flag = 0;
        if (direction == 0) {
            if (map[x][y - 1] == 3) {
                x = 19;
                y = 21;
                transport_flag = 1;
            }
        } else if (direction == 2) {
            if (map[x][y + 1] == 3) {
                x = 4;
                y = 0;
                transport_flag = 1;
            }
        }
        if (!transport_flag) {
            if (direction == 0) --y;
            else if (direction == 1) ++x;
            else if (direction == 2) ++y;
            else if (direction == 3) --x;
        }

    }
    emit pos_changed();
    if (direction >= 0 && direction <= 3) last_direction = direction;

    if (type == 4)
        time_interval = const_ti + \
                (rand() % (2 * (5 + game -> Level())) - 5 - game -> Level()) * 30;

    //timer interval
    if (fri_flag == 4 || fri_flag == 3 || fri_flag == 2) move_timer -> setInterval(100);
    else if (fri_flag == 1) move_timer -> setInterval(400);
    else if (fri_flag == 0) move_timer -> setInterval(time_interval);
    ++t;
}
