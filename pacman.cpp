#include "game.h"
#include "pacman.h"

Pacman::Pacman(Game *p) : Char(p, 0)
{
    x = 20;
    y = 12;
    direction = -1;

    connect(this, SIGNAL(pos_changed()), game, SLOT(pacman_move()));
}

void Pacman::move()
{
    if (game -> Mode() == -1) {
        move_timer -> setInterval(10);
        return;
    }

    if (direction != game -> change_direction) {
        if (game -> change_direction == 0) {
            if (map[x][y - 1]== 0)
                direction = game -> change_direction;
        } else if (game -> change_direction == 1) {
            if (map[x + 1][y] == 0)
                direction = game -> change_direction;
        } else if (game -> change_direction == 2) {
            if (map[x][y + 1] == 0)
                direction = game -> change_direction;
        } else if (game -> change_direction == 3) {
            if (map[x - 1][y] == 0)
                direction = game -> change_direction;
        }
    }
    if (direction >=0 && direction <= 3) last_direction = direction;

    bool move_flag = 0;
    if (direction == 0) {
        if (y > 0 && map[x][y - 1] == 0) {
            y -= 1;
            move_flag = 1;
        }
    } else if (direction == 1) {
        if (x < WIDTH - 1 && map[x + 1][y] == 0) {
            x += 1;
            move_flag = 1;
        }
    }  else if (direction == 2) {
        if (y < LENGTH - 1 && map[x][y + 1] == 0) {
            y += 1;
            move_flag = 1;
        }
    }  else if (direction == 3) {
        if (x > 0 && map[x - 1][y] == 0) {
            x -= 1;
            move_flag = 1;
        }
    }
    if (direction == 0) {//transport
        if (map[x][y - 1] == 3) {
            x = 19;
            y = 21;
            move_flag = 1;
        }
    } else if (direction == 2) {
        if (map[x][y + 1] == 3) {
            x = 4;
            y = 0;
            move_flag = 1;
        }
    }

    if (move_flag) {
        emit pos_changed();
        move_timer -> setInterval(time_interval);
    } else {
        move_timer -> setInterval(10);
    }

}
