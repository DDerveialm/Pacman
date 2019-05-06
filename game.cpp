#include "game.h"

#include <cmath>
#include <ctime>
#include <QDebug>

Game::Game()
{
    //Init status
    init(map);
    for (int i = 0; i < 6; ++i) c[i] = nullptr;

    srand((unsigned)time(nullptr));

    //sounds
    start_sound = new QSoundEffect(this);
    start_sound -> setSource(QUrl::fromLocalFile(":/sounds/start"));
    start_sound -> setVolume(1);
    munch_sound = new QSoundEffect(this);
    munch_sound -> setSource(QUrl::fromLocalFile(":/sounds/munch"));
    munch_sound -> setVolume(0.6);
    for (int i = 0; i < 10; ++i) {
        chomp_sound[i] = new QSoundEffect(this);
        chomp_sound[i] -> setSource(QUrl::fromLocalFile(":/sounds/chomp"));
        chomp_sound[i] -> setVolume(1);
        sd_sound[i] = new QSoundEffect(this);
        sd_sound[i] -> setSource(QUrl::fromLocalFile(":/sounds/sd"));
        sd_sound[i] -> setVolume(0.3);
    }
    eatghost_sound = new QSoundEffect(this);
    eatghost_sound -> setSource(QUrl::fromLocalFile(":/sounds/eatghost"));
    eatghost_sound -> setVolume(1);
    death_sound = new QSoundEffect(this);
    death_sound -> setSource(QUrl::fromLocalFile(":/sounds/death"));
    death_sound -> setVolume(1);

    //timer
    start_timer = new QTimer(this);
    start_timer -> setTimerType(Qt::PreciseTimer);
    start_timer -> setSingleShot(true);
    start_timer -> setInterval(4500);
    connect(start_timer, SIGNAL(timeout()), this, SLOT(start()));

    fri_timer = new QTimer(this);
    fri_timer -> setTimerType(Qt::PreciseTimer);
    fri_timer -> setSingleShot(true);
    connect(fri_timer, SIGNAL(timeout()), this, SLOT(frightened_mode()));

    setting();
}

void Game::set_dir(int d)
{
    if (d >= 0 && d <= 3) change_direction = d;
}

const int &Game::Level()
{
    return level;
}

const int& Game::Mode()
{
    return mode;
}

const int& Game::Score()
{
    return score;
}

void Game::setting()
{
    if (!c[0]) {
        c[0] = new Pacman(this);
        connect(c[0], SIGNAL(pos_changed()), this, SLOT(pacman_move()));
    }
    if (level == 1 || level == 2 || level == 3) {
        if (level == 1) {
            if (!c[1]) c[1]= new Blinky(this);
            if (!c[2]) c[2]= new Pinky(this);
            if (!c[3]) c[3] = new Inky(this);
            if (!c[4]) c[4] = new Clyde(this);
            //speed
            c[0] -> time_interval = 150;
            if (c[1]) c[1] -> time_interval = 190;
            if (c[2]) c[2] -> time_interval = 200;
            if (c[3]) c[3] -> time_interval = 200;
            if (c[4]) c[4] -> time_interval = 260;
        } else if (level == 2) {
            if (!c[1]) c[1]= new Blinky(this);
            if (!c[2]) c[2]= new Pinky(this);
            if (!c[3]) c[3] = new Inky(this);
            if (!c[4]) c[4] = new Clyde(this);
            if (!c[5]) c[5] = new Devil(this);
            //speed
            c[0] -> time_interval = 130;
            if (c[1]) c[1] -> time_interval = 200;
            if (c[2]) c[2] -> time_interval = 220;
            if (c[3]) c[3] -> time_interval = 190;
            if (c[4]) c[4] -> time_interval = 280;
            if (c[5]) c[5] -> time_interval = 200;
        } else if (level == 3) {
            if (!c[1]) c[1]= new Blinky(this);
            if (!c[2]) c[2]= new Pinky(this);
            if (!c[3]) c[3] = new Inky(this);
            if (!c[4]) c[4] = new Clyde(this);
            if (!c[5]) c[5] = new Devil(this);
            //speed
            c[0] -> time_interval = 120;
            if (c[1]) c[1] -> time_interval = 200;
            if (c[2]) c[2] -> time_interval = 240;
            if (c[3]) c[3] -> time_interval = 180;
            if (c[4]) c[4] -> time_interval = 300;
            if (c[5]) c[5] -> time_interval = 250;
        }

        edible();
        mode = -1;
        c[0] -> direction = -1;
        if (fri_timer -> isActive()) fri_timer -> stop();
        do {
            c[0] -> x = rand() % WIDTH;
            c[0] -> y = rand() % LENGTH;
        } while (map[c[0] -> x][c[0] -> y][0] || map[c[0] -> x][c[0] -> y][1] == 2 || map[c[0] -> x][c[0] -> y][1] == 3\
                 || (c[0] -> x >= 19 && c[0] -> x <= 21 && c[0] -> y >= 10 && c[0] -> y <= 13));
        map[c[0] -> x][c[0] -> y][1] = 0;
        for (int i = 1; i < 6; ++i) if (c[i]) c[i] -> init();
    } else {
        for (int i = 1; i < 6; ++i)
            if (c[i]) {
                delete c[i];
                c[i] = nullptr;
            }
        for (int i = 0; i < WIDTH; ++i)
            for (int j = 0; j < LENGTH; ++j)
                if (i == 0 || i == WIDTH - 1 || j == 0 || j == LENGTH - 1) {
                    map[i][j][0] = 1;
                } else if (map[i][j][0]) {
                    map[i][j][0] = 0;
                    if (pow(i - 17, 2) + pow(j - 11, 2) >= 64) map[i][j][1] = 4;
                }
       c[0] -> time_interval = 120;
       c[0] -> map_copy();
        mode = 4;
    }
}

void Game::edible()
{
    for (int i = 0; i < WIDTH; ++i)
        for (int j = 0; j < LENGTH; ++j) {
            if (map[i][j][0] == 0) {
                //1: dots
                //2: special dot
                //3: power pellet
                if (i > 18 && i < 22 && j > 8 && j < 14) map[i][j][1] = 0;//birth place of ghosts
                else if (i > 9 && i < 14 && j > 0 && j < 8) map[i][j][1] = 2;//2
                else if (i > 15 && i < 21 && j > 0 && j < 9 && !((i == 16 || i == 17) && j == 7)) map[i][j][1] = 2;//5
                else if (i > 22 && i < 28 && j > 0 && j < 10 && !(i == 27 && (j > 1 && j < 6))) map[i][j][1] = 2;//6
                else if (i == 4 && j > 0 && j < 5) map[i][j][1] = 0;
                else if (i == 19 && j > 15 && j < 21) map[i][j][1] = 0;
                else {
                    map[i][j][1] = 1;
                    ++remaining_beans;
                }
            } else map[i][j][1] = 0;
            if ((i == 1 && j == 5) || (i == 31 && j == 5) || (i == 14 && j == 12)\
                                     || (i == 1 && j == 15) || (i == 31 && j == 15)) map[i][j][1] = 3;
        }
}

void Game::win()
{
    if (level < 4) ++level;
    setting();
}

void Game::coin_inserted()
{
    start_sound -> play();
    start_timer -> start();
}

void Game::start()
{
    mode = 0;
}

void Game::pacman_move()
{
    if (!munch_sound -> isPlaying()) munch_sound -> play();
    if (mode != 3 && mode != 4) check_pos();

    if (map[c[0] -> x][c[0] -> y][1] == 1) {
        score += 10;
        --remaining_beans;
        if (c[1]) {
            if (remaining_beans == 10) c[1] -> time_interval -= 20;
            else if (remaining_beans == 30) c[1] -> time_interval -= 15;
            else if (remaining_beans == 60) c[1] -> time_interval -= 10;
            else if (remaining_beans == 100) c[1] -> time_interval -= 5;
        }
        //qDebug() << c[1] -> time_interval;
        map[c[0] -> x][c[0] -> y][1] = 0;
        for (int i = 0; i < 10; ++i)
            if (chomp_sound[i] -> isPlaying() == 0) {
                chomp_sound[i] -> play();
                break;
            }
    } else if (map[c[0] -> x][c[0] -> y][1] == 2) {
        score += 30;
        map[c[0] -> x][c[0] -> y][1] = 0;
        for (int i = 0; i < 10; ++i)
            if (sd_sound[i] -> isPlaying() == 0) {
                sd_sound[i] -> play();
                break;
            }
    } else if (map[c[0] -> x][c[0] -> y][1] == 3) {
        if (mode != 4) {
            mode = 0;
            emit frightened_mode();
        }
        score += 50;
        map[c[0] -> x][c[0] -> y][1] = 0;
    } else if (map[c[0] -> x][c[0] -> y][1] == 4) {
        score += 666;
        map[c[0] -> x][c[0] -> y][1] = 0;
    }

    if (mode == 4){
        map[c[0] -> x][c[0] -> y][1] = 5;
    }
    if (mode != 3 && mode != 4) check_win();
}

void Game::check_win()
{
    int flag = 1;
    for (int i = 0; i < WIDTH; ++i)
        for (int j = 0; j < LENGTH; ++j)
            if (map[i][j][1]) flag = 0;
    if (flag && mode != 4) {
        win();
        qDebug() << "Win";
    }
}

void Game::check_pos()
{
    if (mode == 3 || mode == 4) return;
    for (int i = 1; i < 6; ++i) {
        if (c[i] && c[0] -> x == c[i] -> X() && c[0] -> y == c[i] -> Y()) {
            if (c[i] -> Flag() == 0) {
                mode = 3;
                c[0] -> x = 20;
                c[0] -> y = 12;
                qDebug() << "Game over";
                death_sound -> play();
                break;
            } else if (c[i] -> Flag() == 1) {
                c[i] -> fri_flag = 4;
                score += 100 * pow(2, i);
                qDebug() << "eat c[" + QString::number(i) + "]";
                eatghost_sound -> play();
            }
        }
    }
}

void Game::frightened_mode()
{
    if (mode == 0) {
        mode = 2;
        for (int i = 1; i < 5; ++i) {
            if (c[i] && c[i] -> fri_flag == 0)
                c[i] -> fri_flag = 1;
        }
        fri_timer -> start(9000 - level * 1000);
    } else if (mode == 2) {
        mode = 1;
        fri_timer -> start(2000);
    } else if (mode == 1 || mode == 3) {
        for (int i = 1; i < 5; ++i) {
            if (c[i] && c[i] -> fri_flag == 1)
                c[i] -> fri_flag = 0;
        }
        if (mode == 1) mode = 0;
    }
}
