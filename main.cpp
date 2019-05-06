#include <game.h>
#include <ui.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Ui *ui = new Ui(new Game());
    ui -> show();

    return a.exec();
}
