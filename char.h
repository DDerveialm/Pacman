#ifndef CHAR_H
#define CHAR_H

#include <QObject>
#include <QTimer>

#define WIDTH 33
#define LENGTH 22

class Game;

class Char : public QObject
{
    friend Game;
    Q_OBJECT

public:
    Char(Game *, int);
    const int &X();
    const int &Y();
    const int &Type();
    const int &Flag();//ghost
    const int &Dir();
    const int &Direction();
    int Time_interval();
    virtual void init();
    virtual ~Char();

protected:
    Game *game;
    int map[WIDTH][LENGTH];
    int type, x, y, direction = -1, last_direction = 0, time_interval = 200, fri_flag = 0;
    QTimer *move_timer;
    void map_copy();

signals:
    void pos_changed();

protected slots:
    virtual void move() =0;

};

#endif // CHAR_H
