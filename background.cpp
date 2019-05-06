#include "background.h"

Background::Background(Game *g, Ui *u) : game(g), ui(u)
{
    setGeometry(0, 0, 1100, 900);
    setStyleSheet("background-color:black");

    timer = new QTimer(this);
    timer -> setTimerType(Qt::PreciseTimer);
    timer -> start(300);
    connect(timer, SIGNAL(timeout()), this, SLOT(power_pellet_flicker()));

    se_timer = new QTimer(this);
    se_timer -> setTimerType(Qt::PreciseTimer);
    se_timer -> setInterval(3);
    connect(se_timer, SIGNAL(timeout()), this, SLOT(se()));
}

void Background::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (ui -> Coin_flag() == 0) {
        painter.drawPixmap(250, 40, QPixmap(":/images/insert").scaledToHeight(100));
        return ;
    }
    if (game -> Mode() == -1) painter.drawPixmap(real_x(18) - 10, real_y(14) - 10, QPixmap(":/images/start").scaled(160, 80));
    for (int i = 0; i < WIDTH; ++i) {
        int j;
        for (j = 0; j < LENGTH; ++j) {
            if (i * LENGTH + j == se_flag) break;
            if (game -> map[i][j][0] == 1) {
                if (i > 1 && i < 10 && j > 5 && j < 15)//D
                    painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                else if (i > 10 && i < 17 && j > 7 && j < 15)//e
                    painter.setPen(QPen(Qt::blue, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                else if (i > 17 && i < 23 && j > 8 && j < 15)//v
                    painter.setPen(QPen(Qt::yellow, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                else if (i > 23 && i < 27 && j > 6 && j < 15)//i
                    painter.setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                else if (i > 27 && i < 31 && j > 5 && j < 15)//l
                    painter.setPen(QPen(Qt::cyan, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                else
                    painter.setPen(QPen(Qt::blue, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                int count = 0, flag = 0;

                if (i + 1 < WIDTH && (game -> map[i + 1][j][0] == 2 || game -> map[i + 1][j][0] == 7)) continue;
                if (j - 1 >= 0 && (game -> map[i][j - 1][0] == 2 || game -> map[i][j - 1][0] == 7)) continue;
                if (j + 1 < LENGTH && (game -> map[i][j + 1][0] == 2 || game -> map[i][j + 1][0] == 7)) continue;
                else if (i - 1 >= 0 && (game -> map[i - 1][j][0] == 2 || game -> map[i - 1][j][0] == 7)) continue;
                if (i + 1 < WIDTH && game -> map[i + 1][j][0] != 0) ++count;
                else flag = 1;
                if (i - 1 >= 0 && game -> map[i - 1][j][0] != 0) ++count;
                else flag = 1;
                if (j + 1 < LENGTH && game -> map[i][j + 1][0] != 0) ++count;
                else flag = 2;
                if (j - 1 >= 0 && game -> map[i][j - 1][0] != 0) ++count;
                else flag = 2;
                if (count == 2) {
                    if (i + 1 < WIDTH && (game -> map[i + 1][j][0] == 1 || game -> map[i + 1][j][0] == 5))
                        painter.drawLine(real_x(i), real_y(j), real_x(i + 1), real_y(j));
                    if (i - 1 >= 0 && (game -> map[i - 1][j][0] == 1 || game -> map[i - 1][j][0] == 5))
                        painter.drawLine(real_x(i), real_y(j), real_x(i - 1), real_y(j));
                    if (j + 1 < LENGTH && (game -> map[i][j + 1][0] == 1 || game -> map[i][j + 1][0] == 5))
                        painter.drawLine(real_x(i), real_y(j), real_x(i), real_y(j + 1));
                    if (j - 1 >= 0 && (game -> map[i][j - 1][0] == 1 || game -> map[i][j - 1][0] == 5))
                        painter.drawLine(real_x(i), real_y(j), real_x(i), real_y(j - 1));
                } else if (count == 3) {
                    if (flag == 1) {
                        painter.drawLine(real_x(i), real_y(j), real_x(i), real_y(j + 1));
                        painter.drawLine(real_x(i), real_y(j), real_x(i), real_y(j - 1));
                    } else if (flag == 2) {
                        painter.drawLine(real_x(i), real_y(j), real_x(i + 1), real_y(j));
                        painter.drawLine(real_x(i), real_y(j), real_x(i - 1), real_y(j));
                    }
                }
            } else if (game -> map[i][j][0] == 2) {
                painter.setPen(QPen(Qt::white, 3, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
                painter.drawLine(real_x(i), real_y(j), real_x(i + 1), real_y(j));
                painter.drawLine(real_x(i), real_y(j), real_x(i - 1), real_y(j));
            } else if (game -> map[i][j][0] == 4) {
                if (i > 1 && i < 10 && j > 5 && j < 15)//D
                    painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                else if (i > 10 && i < 17 && j > 7 && j < 15)//e
                    painter.setPen(QPen(Qt::blue, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                else if (i > 17 && i < 23 && j > 8 && j < 15)//v
                    painter.setPen(QPen(Qt::yellow, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                else if (i > 23 && i < 27 && j > 6 && j < 15)//i
                    painter.setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                else if (i > 27 && i < 31 && j > 5 && j < 15)//l
                    painter.setPen(QPen(Qt::cyan, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                else
                    painter.setPen(QPen(Qt::blue, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                int count = 0, flag = 0;
                if (game -> map[i + 1][j][0] == 4) ++count;
                else flag = 1;
                if (game -> map[i - 1][j][0] == 4) ++count;
                else flag = 1;
                if (game -> map[i][j + 1][0] == 4) ++count;
                else flag = 2;
                if (game -> map[i][j - 1][0] == 4) ++count;
                else flag = 2;
                if (count == 2) {
                    if (game -> map[i + 1][j][0] == 4) painter.drawLine(real_x(i), real_y(j), real_x(i + 1), real_y(j));
                    if (game -> map[i - 1][j][0] == 4) painter.drawLine(real_x(i), real_y(j), real_x(i - 1), real_y(j));
                    if (game -> map[i][j + 1][0] == 4) painter.drawLine(real_x(i), real_y(j), real_x(i), real_y(j + 1));
                    if (game -> map[i][j - 1][0] == 4) painter.drawLine(real_x(i), real_y(j), real_x(i), real_y(j - 1));
                } else if (count == 3) {
                    if (flag == 1) {
                        painter.drawLine(real_x(i), real_y(j), real_x(i), real_y(j + 1));
                        painter.drawLine(real_x(i), real_y(j), real_x(i), real_y(j - 1));
                    } else if (flag == 2) {
                        painter.drawLine(real_x(i), real_y(j), real_x(i + 1), real_y(j));
                        painter.drawLine(real_x(i), real_y(j), real_x(i - 1), real_y(j));
                    }
                }
            }  else if (game -> map[i][j][0] == 6) {
                if (i > 1 && i < 10 && j > 5 && j < 15)//D
                    painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                else if (i > 10 && i < 17 && j > 7 && j < 15)//e
                    painter.setPen(QPen(Qt::blue, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                else if (i > 17 && i < 23 && j > 8 && j < 15)//v
                    painter.setPen(QPen(Qt::yellow, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                else if (i > 23 && i < 27 && j > 6 && j < 15)//i
                    painter.setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                else if (i > 27 && i < 31 && j > 5 && j < 15)//l
                    painter.setPen(QPen(Qt::cyan, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                else
                    painter.setPen(QPen(Qt::blue, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                if (game -> map[i + 1][j][0] == 5 && game -> map[i][j + 1][0] == 5)
                    painter.drawLine(real_x(i + 1), real_y(j), real_x(i), real_y(j + 1));
                if (game -> map[i + 1][j][0] == 5 && game -> map[i][j - 1][0] == 5)
                    painter.drawLine(real_x(i + 1), real_y(j), real_x(i), real_y(j - 1));
                if (game -> map[i - 1][j][0] == 5 && game -> map[i][j + 1][0] == 5)
                    painter.drawLine(real_x(i - 1), real_y(j), real_x(i), real_y(j + 1));
                if (game -> map[i - 1][j][0] == 5 && game -> map[i][j - 1][0] == 5)
                    painter.drawLine(real_x(i - 1), real_y(j), real_x(i), real_y(j - 1));
            } else if (game -> map[i][j][0] == 7) {
                painter.setPen(QPen(Qt::blue, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                painter.drawLine(real_x(i), real_y(j + 1), real_x(i), real_y(j - 1));
            }
        }
        if (i * LENGTH + j == se_flag) break;
    }
    //
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            if (i * LENGTH + j == se_flag) break;
            if (game -> map[i][j][0] == 1) {
                if (i > 1 && i < 10 && j > 5 && j < 15) continue;//D
                else if (i > 10 && i < 17 && j > 7 && j < 15) continue;//e
                else if (i > 17 && i < 23 && j > 8 && j < 15) continue;//v
                else if (i > 23 && i < 27 && j > 6 && j < 15) continue;//i
                else if (i > 27 && i < 31 && j > 5 && j < 15) continue;//l
                else painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                int count = 0, flag = 0;
                if (i + 1 < WIDTH && game -> map[i + 1][j][0] == 7) continue;
                if (j - 1 >= 0 && game -> map[i][j - 1][0] == 7) continue;
                if (j + 1 < LENGTH && game -> map[i][j + 1][0] == 7) continue;
                else if (i - 1 >= 0 && game -> map[i - 1][j][0] == 7) continue;
                if (i + 1 < WIDTH && game -> map[i + 1][j][0] != 0) ++count;
                else flag = 1;
                if (i - 1 >= 0 && game -> map[i - 1][j][0] != 0) ++count;
                else flag = 1;
                if (j + 1 < LENGTH && game -> map[i][j + 1][0] != 0) ++count;
                else flag = 2;
                if (j - 1 >= 0 && game -> map[i][j - 1][0] != 0) ++count;
                else flag = 2;
                if (count == 2) {
                    if (i + 1 < WIDTH && (game -> map[i + 1][j][0] == 1 || game -> map[i + 1][j][0] == 5))
                        painter.drawLine(real_x(i), real_y(j), real_x(i + 1), real_y(j));
                    if (i - 1 >= 0 && (game -> map[i - 1][j][0] == 1 || game -> map[i - 1][j][0] == 5))
                        painter.drawLine(real_x(i), real_y(j), real_x(i - 1), real_y(j));
                    if (j + 1 < LENGTH && (game -> map[i][j + 1][0] == 1 || game -> map[i][j + 1][0] == 5))
                        painter.drawLine(real_x(i), real_y(j), real_x(i), real_y(j + 1));
                    if (j - 1 >= 0 && (game -> map[i][j - 1][0] == 1 || game -> map[i][j - 1][0] == 5))
                        painter.drawLine(real_x(i), real_y(j), real_x(i), real_y(j - 1));
                } else if (count == 3) {
                    if (flag == 1) {
                        painter.drawLine(real_x(i), real_y(j), real_x(i), real_y(j + 1));
                        painter.drawLine(real_x(i), real_y(j), real_x(i), real_y(j - 1));
                    } else if (flag == 2) {
                        painter.drawLine(real_x(i), real_y(j), real_x(i + 1), real_y(j));
                        painter.drawLine(real_x(i), real_y(j), real_x(i - 1), real_y(j));
                    }
                }
            } else if (game -> map[i][j][0] == 4) {
                if (i > 1 && i < 10 && j > 5 && j < 15) continue;//D
                else if (i > 10 && i < 17 && j > 7 && j < 15) continue;//e
                else if (i > 17 && i < 23 && j > 8 && j < 15) continue;//v
                else if (i > 23 && i < 27 && j > 6 && j < 15) continue;//i
                else if (i > 27 && i < 31 && j > 5 && j < 15) continue;//l
                else painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                int count = 0, flag = 0;
                if (game -> map[i + 1][j][0] == 4) ++count;
                else flag = 1;
                if (game -> map[i - 1][j][0] == 4) ++count;
                else flag = 1;
                if (game -> map[i][j + 1][0] == 4) ++count;
                else flag = 2;
                if (game -> map[i][j - 1][0] == 4) ++count;
                else flag = 2;
                if (count == 2) {
                    if (game -> map[i + 1][j][0] == 4) painter.drawLine(real_x(i), real_y(j), real_x(i + 1), real_y(j));
                    if (game -> map[i - 1][j][0] == 4) painter.drawLine(real_x(i), real_y(j), real_x(i - 1), real_y(j));
                    if (game -> map[i][j + 1][0] == 4) painter.drawLine(real_x(i), real_y(j), real_x(i), real_y(j + 1));
                    if (game -> map[i][j - 1][0] == 4) painter.drawLine(real_x(i), real_y(j), real_x(i), real_y(j - 1));
                } else if (count == 3) {
                    if (flag == 1) {
                        painter.drawLine(real_x(i), real_y(j), real_x(i), real_y(j + 1));
                        painter.drawLine(real_x(i), real_y(j), real_x(i), real_y(j - 1));
                    } else if (flag == 2) {
                        painter.drawLine(real_x(i), real_y(j), real_x(i + 1), real_y(j));
                        painter.drawLine(real_x(i), real_y(j), real_x(i - 1), real_y(j));
                    }
                }
            }  else if (game -> map[i][j][0] == 6) {
                if (i > 1 && i < 10 && j > 5 && j < 15) continue;//D
                else if (i > 10 && i < 17 && j > 7 && j < 15) continue;//e
                else if (i > 17 && i < 23 && j > 8 && j < 15) continue;//v
                else if (i > 23 && i < 27 && j > 6 && j < 15) continue;//i
                else if (i > 27 && i < 31 && j > 5 && j < 15) continue;//l
                else painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                if (game -> map[i + 1][j][0] == 5 && game -> map[i][j + 1][0] == 5)
                    painter.drawLine(real_x(i + 1), real_y(j), real_x(i), real_y(j + 1));
                if (game -> map[i + 1][j][0] == 5 && game -> map[i][j - 1][0] == 5)
                    painter.drawLine(real_x(i + 1), real_y(j), real_x(i), real_y(j - 1));
                if (game -> map[i - 1][j][0] == 5 && game -> map[i][j + 1][0] == 5)
                    painter.drawLine(real_x(i - 1), real_y(j), real_x(i), real_y(j + 1));
                if (game -> map[i - 1][j][0] == 5 && game -> map[i][j - 1][0] == 5)
                    painter.drawLine(real_x(i - 1), real_y(j), real_x(i), real_y(j - 1));
            } else if (game -> map[i][j][0] == 7) {
                painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                painter.drawLine(real_x(i), real_y(j + 1), real_x(i), real_y(j - 1));
            }
        }
    }

    if (game -> Mode() == 4) {
        painter.drawPixmap(real_x(10), real_y(4), QPixmap(":/images/surprise").scaled(400, 400));
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    for (int i = 0; i < WIDTH; ++i)
        for (int j = 0; j < LENGTH; ++j) {
            if (game -> map[i][j][1] == 1) painter.drawPixmap(real_x(i) - 2, real_y(j) - 2, QPixmap(":/images/dot1").scaled(5, 5));
            else if (game -> map[i][j][1] == 2) painter.drawPixmap(real_x(i) - 5, real_y(j) - 5, QPixmap(":/images/dot2").scaled(10, 10));
            else if (game -> map[i][j][1] == 3 && time % 2 == 0) painter.drawPixmap(real_x(i) - 8, real_y(j) - 8, QPixmap(":/images/dot3").scaled(16, 16));
            else if (game -> map[i][j][1] == 4) painter.drawPixmap(real_x(i) - 10, real_y(j) - 10, QPixmap(":/images/dot4").scaled(20, 20));
            else if (game -> Mode() == 4 && game -> map[i][j][1] != 5 && (i != 0 && i != WIDTH - 1) && (j != 0 && j != LENGTH - 1))
                painter.drawRect(real_x(i) - 15, real_y(j) - 15, 30, 30);
        }
    if (time % 2) painter.drawPixmap(250, 40, QPixmap(":/images/title0").scaledToHeight(100));
    else painter.drawPixmap(250, 40, QPixmap(":/images/title1").scaledToHeight(100));

}

void Background::se()
{
    se_flag += 10;
    update();
    if (se_flag >= WIDTH * LENGTH) se_timer -> stop();
}

void Background::power_pellet_flicker()
{
    if (game -> Mode() == -1) return;
    ++time;
    if (game -> Mode() != 4) {
        update();
    } else update(250, 40, 400, 100);
}
