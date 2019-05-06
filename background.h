#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "game.h"
#include "func.h"
#include "ui.h"
#include <QWidget>
#include <QPainter>
#include <QTimer>

class Game;

class Background : public QWidget
{
    friend Ui;
    Q_OBJECT
public:
    Background(Game *, Ui *);

protected:
    void paintEvent(QPaintEvent *);

private:
    Game *game;
    Ui *ui;
    int time = 0, se_flag = 0;
    QTimer *timer, *se_timer;

private slots:
    void se();
    void power_pellet_flicker();

};

#endif // BACKGROUND_H
