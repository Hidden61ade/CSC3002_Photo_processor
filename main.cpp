#include "mainwindow.h"

#include "testwindow.h"

#include <QApplication>

#include "lasso.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    printf("hello");
//    Lasso lasso("D:/11111.jpg");
//    lasso.start();

    return a.exec();
}
