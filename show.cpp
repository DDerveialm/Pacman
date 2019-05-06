#include "game.h"
#include "show.h"
#include <QString>

#define Nof_segments 10

Show::Show(Game *ptr, int t) :type(t), game(ptr)
{
    xx = game -> c[type] -> X();
    yy = game -> c[type] -> Y();
    setPos(real_x(xx), real_y(yy));

    if (type == 0) {
        setPixmap(QPixmap(":/images/p0").scaled(30, 30));
        setOffset(-15, -15);
    } else if (type == 5) {
        if (game -> Level() == 2) {
            setPixmap(QPixmap(":/images/50").scaled(80, 80));
            setOffset(-40, -40);
        } else {
            setPixmap(QPixmap(":/images/50").scaled(40, 40));
            setOffset(-20, -20);
        }
    } else {
        setPixmap(QPixmap(":/images/" + QString::number(type) + "0").scaled(40, 40));
        setOffset(-20, -20);
    }

    //timer
    timer = new QTimer(this);
    timer -> setTimerType(Qt::PreciseTimer);
    connect(timer, SIGNAL(timeout()), this, SLOT(segmented_move()));

    opacity_timer = new QTimer(this);
    opacity_timer -> setTimerType(Qt::PreciseTimer);
    opacity_timer -> setInterval(40);
    connect(opacity_timer, SIGNAL(timeout()), this, SLOT(transprant()));

    if (type == 5) setOpacity(0.7);
}

void Show::move()
{
    if (timer -> isActive()) timer -> stop();
    setPos(real_x(xx), real_y(yy));

    int nx;
    int ny;
    nx = game -> c[type] -> X();
    ny = game -> c[type] -> Y();

    if ((nx == 4 && ny == 0) || (nx == 19 && ny == 21)) {//transport
        setPos(real_x(nx), real_y(ny));
        xx = nx;
        yy = ny;
        return ;
    }

    ix = (real_x(nx) - real_x(xx)) / static_cast<double>(Nof_segments);
    iy = (real_y(ny) - real_y(yy)) / static_cast<double>(Nof_segments);
    int dir = game -> c[type] -> Direction();
    times = 0;
    timer -> start(game -> c[type] -> Time_interval() / Nof_segments);

    if (type == 0) {
        setRotation(90 * (dir + 1));
        setPixmap(QPixmap(":/images/p1").scaled(30, 30));
    } else {
        if (game -> c[type] -> Flag() == 4 || game -> c[type] -> Flag() == 3) ;
        else if (game -> c[type] -> Flag() == 2)
            setPixmap(QPixmap(":/images/dead" + QString::number(dir)).scaled(40, 20));
        else if (game -> c[type] -> Flag() == 1 && game -> Mode() == 2)
            setPixmap(QPixmap(":/images/f" + QString::number(dir)).scaled(40, 40));
        else {
            if (type == 5 && game -> Level() == 2) {
                setPixmap(QPixmap(":/images/5" + QString::number(dir)).scaled(80, 80));
                setOffset(-40, -40);
            } else {
                setPixmap(QPixmap(":/images/" + QString::number(type) + QString::number(dir)).scaled(40, 40));
                setOffset(-20, -20);
            }
        }
    }
    xx = nx;
    yy = ny;
}

void Show::warning()
{
    if (game -> c[type] -> Flag() != 1) return ;

    int dir = game -> c[type] -> Direction();
    if (flag == 0) {
        flag = 1;
        setPixmap(QPixmap(":/images/w" + QString::number(dir)).scaled(40, 40));
    } else {
        flag = 0;
        setPixmap(QPixmap(":/images/f" + QString::number(dir)).scaled(40, 40));
    }
}

void Show::frighten()
{
    if (game -> c[type] -> Flag() != 1) return;
    setPixmap(QPixmap(":/images/f" + QString::number(game -> c[type] -> Direction())).scaled(40, 40));
}

void Show::back()
{
    if (type == 0 || type == 5) return ;

    if (game -> c[type] -> Flag() == 0) {
        setPixmap(QPixmap(":/images/" + QString::number(type)\
                          + QString::number(game -> c[type] -> Direction())).scaled(40, 40));
    } else if (game -> c[type] -> Flag() == 1) {
        setPixmap(QPixmap(":/images/f" + QString::number(game -> c[type] -> Direction())).scaled(40, 40));
    }
}

void Show::segmented_move()
{
    ++times;
    if (times <= Nof_segments) {
        if (type == 0)
            if (times == Nof_segments / 2)
                setPixmap(QPixmap(":/images/p0").scaled(30, 30));
        setPos(x() + ix, y() + iy);
    } else {
        if (type == 0 && game -> Mode() != -1)
            setPixmap(QPixmap(":/images/p1").scaled(30, 30));
        timer -> stop();
    }
}

void Show::transprant()
{
    if (opacity() == 1.) setOpacity(0.6);
    setOpacity(effectiveOpacity() - 0.05);
    setScale(scale() + 0.3);
    if (effectiveOpacity() < 0.1) {
        opacity_timer -> stop();
        setOpacity(1);
        setScale(1);
    }
}
