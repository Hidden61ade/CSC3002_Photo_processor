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
//    Lasso lasso;
//    lasso.set_image("D:/11111.jpg");  // 替换为你的图片路径
//    lasso.start();
    return a.exec();
}
