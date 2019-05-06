#ifndef UI_H
#define UI_H

#include "show.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QPushButton>

class Game;
class Background;

class Ui : public QGraphicsView
{
    Q_OBJECT
public:
    Ui(Game *);
    const int &Coin_flag();

private:
    Game *kernel;
    QPushButton *coin;
    int ui_mode;
    void keyPressEvent(QKeyEvent *);

    int ui_score;
    QString level[4];
    QGraphicsTextItem *dashboard;
    Show *s[6];
    QGraphicsScene *scene;
    Background *background;

    QTimer *check_timer, *warning_timer;

    int coin_flag = 0;

signals:
    void show_fri();
    void show_back();

public slots:
    void check();

private slots:
    void coin_clicked();

};

#endif // UI_H
