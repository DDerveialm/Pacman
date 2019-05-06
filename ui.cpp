#include "game.h"
#include "ui.h"
#include <QBitmap>
#include "background.h"

Ui::Ui(Game *ptr) : kernel(ptr), ui_mode(-2), ui_score(ptr -> Score())
{
    // create the scene
    scene = new QGraphicsScene();
    scene -> setSceneRect(0, 0, 1100, 900);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1100 + 2, 900 + 2);

    // draw background
    background = new Background(kernel, this);
    scene -> addWidget(background);

    //init status
    for (int i = 0; i < 6; ++i) s[i] = nullptr;

    warning_timer = new QTimer(this);
    warning_timer -> setTimerType(Qt::PreciseTimer);
    warning_timer -> setInterval(100);

    check_timer = new QTimer(this);
    check_timer -> setTimerType(Qt::PreciseTimer);
    connect(check_timer, SIGNAL(timeout()), this, SLOT(check()));
    check_timer -> setSingleShot(true);
    check_timer -> start(3);

    //dashboard
    level[0] = QString("EZ  LEVEL    SCORE:  ");
    level[1] = QString("HARD  LEVEL    SCORE:  ");
    level[2] = QString("DEVIL  LEVEL    SCORE:  ");
    level[3] = QString("FINAL SCORE:  ");

    dashboard = new QGraphicsTextItem();
    dashboard -> setPos(650, 150);
    dashboard -> setScale(2);
    dashboard -> setDefaultTextColor(Qt::white);
    dashboard -> setPlainText(level[kernel -> Level() - 1] + QString::number(kernel -> Score()));
    scene -> addItem(dashboard);

    coin = new QPushButton(this);
    coin -> setMask((QPixmap(":/images/coin").scaled(80, 80)).mask());
    coin -> setIconSize(QSize(80, 80));
    coin -> setIcon(QIcon(QPixmap(":/images/coin").scaled(80, 80)));
    coin -> setGeometry(450, 150, 80, 80);
    connect(coin, SIGNAL(clicked()), this, SLOT(coin_clicked()));

}

const int &Ui::Coin_flag()
{
    return coin_flag;
}

void Ui::keyPressEvent(QKeyEvent *event)
{
    if (event -> key() == Qt::Key_Up) kernel -> set_dir(0);
    else if (event -> key() == Qt::Key_Right) kernel -> set_dir(1);
    else if (event -> key() == Qt::Key_Down) kernel -> set_dir(2);
    else if (event -> key() == Qt::Key_Left) kernel -> set_dir(3);
}

void Ui::check()
{
    for (int i = 0; i < 6; ++i) {
        if (!s[i] && kernel -> c[i]) {
            s[i] = new Show(kernel, kernel -> c[i] -> Type());
            scene -> addItem(s[i]);
            if (i != 0) {
                connect(warning_timer, SIGNAL(timeout()), s[i], SLOT(warning()));
                connect(this, SIGNAL(show_fri()), s[i], SLOT(frighten()));
                connect(this, SIGNAL(show_back()), s[i], SLOT(back()));
            }
        } else if (s[i] && !kernel -> c[i]) {
            delete s[i];
            s[i] = nullptr;
        }
    }

    for (int i = 0; i < 6; ++i) {
        if (s[i]) {
            if (s[i] -> xx != kernel -> c[i] -> X() || s[i] -> yy != kernel -> c[i] -> Y())
                s[i] -> move();
            if (kernel -> c[i] -> Flag() == 4 || kernel -> c[i] -> Flag() == 3)
                if (!s[i] -> opacity_timer -> isActive())
                    s[i] -> opacity_timer -> start();
        }
    }

    if (ui_mode != kernel -> Mode()) {
        if (ui_mode == 1) {
            warning_timer -> stop();
            emit show_back();
        }
        ui_mode = kernel -> Mode();
        if (ui_mode == 2) emit show_fri();
        if (ui_mode == 1) warning_timer -> start();
        if (ui_mode == -1 || ui_mode == 4) {
            if (ui_mode == -1) {
                coin -> show();
                coin_flag = 0;
                background -> se_flag = 0;
                if (s[0]) s[0] -> hide();
            }
            if (kernel -> c[0] -> Dir() == -1) s[0] -> setPixmap(QPixmap(":/images/p0").scaled(30, 30));
            background -> time = 0;
            background -> update();
        }
        if (ui_mode == 3) if (s[0]) s[0] -> setOpacity(0.1);
    }

    if (ui_score != kernel -> Score()) {
        ui_score = kernel -> Score();
        dashboard -> setPlainText(level[kernel -> Level() - 1] + QString::number(ui_score));
    }
    check_timer -> start();
}

void Ui::coin_clicked()
{
    if (coin_flag == 1) return;
    coin_flag = 1;
    coin -> hide();
    if (s[0]) s[0] -> show();
    kernel -> coin_inserted();
    background -> se_timer -> start();
}
