#ifndef SHOW_H
#define SHOW_H

#include "func.h"

#include <QGraphicsPathItem>
#include <QTimer>

class Game;

class Show : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Show(Game *, int);
    int type, xx, yy;
    void move();
    QTimer *opacity_timer;

public slots:
    void warning();
    void frighten();
    void back();

private:
    Game *game;
    QTimer *timer;
    int times, flag = 0;
    double ix, iy;

private slots:
    void segmented_move();
    void transprant();

};

#endif // SHOW_H
