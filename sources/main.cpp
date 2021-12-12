#include "mainwindow.h"
#include "gestionClick.h"
#include <QDesktopWidget>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    int x = (QApplication::desktop()->width())/6;
//    int y = (QApplication::desktop()->height())/7;
    MainWindow w;
    w.show();
//    w.move(x,y);
    return a.exec();
}
