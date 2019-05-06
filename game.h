#ifndef GAME_H
#define GAME_H

#include "pacman.h"
#include "blinky.h"
#include "pinky.h"
#include "inky.h"
#include "clyde.h"
#include "devil.h"
#include "func.h"

#include <QObject>
#include <QTimer>
#include <QSoundEffect>

class Background;

class Game :public QObject
{
    Q_OBJECT
    friend Background;
    friend Char;
    friend Pacman;

public:
    Game();
    void set_dir(int);
    const int &Level();
    const int &Mode();
    const int &Score();
    Char *c[6];
    void coin_inserted();

private:
    int map[WIDTH][LENGTH][2];
    int  level = 1, change_direction = -1, mode = -1, score = 0, remaining_beans = 0;
    //mode 0: normal
    //mode 1: f_mode ending
    //mode 2: frightened
    //mode 3: dead
    //mode 4: win
    QTimer *start_timer;
    QTimer *fri_timer;
    QSoundEffect *start_sound, *munch_sound, *chomp_sound[10], *sd_sound[10], *eatghost_sound, *death_sound;
    void setting();
    void edible();
    void win();

private slots:
    void start();
    void pacman_move();
    void check_win();
    void check_pos();
    void frightened_mode();

};

#endif // GAME_H
