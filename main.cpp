#include "mainwindow.h"

#include "testwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    printf("hello");
    return a.exec();
}
