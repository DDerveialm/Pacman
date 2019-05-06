#include "game.h"
#include "char.h"

Char::Char(Game *p, int t) : game(p), type(t)
{
    map_copy();

    move_timer = new QTimer(this);
    move_timer -> setTimerType(Qt::PreciseTimer);
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move()));
    move_timer -> start(time_interval);
}

const int &Char::X()
{
    return x;
}

const int &Char::Y()
{
    return y;
}

const int &Char::Type()
{
    return type;
}

const int &Char::Flag()
{
    return fri_flag;
}

const int &Char::Dir()
{
    return direction;
}

const int &Char::Direction()
{
    return last_direction;
}

int Char::Time_interval()
{
    return move_timer ->interval();
}

void Char::init()
{

}

Char::~Char()
{

}

void Char::map_copy()
{
    for (int i = 0; i < WIDTH; ++i)
        for (int j = 0; j < LENGTH; ++j) {
            map[i][j] = game -> map[i][j][0];
        }
}
