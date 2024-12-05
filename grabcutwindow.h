#ifndef GRABCUTWINDOW_H
#define GRABCUTWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include<QString>
#include<QMessageBox>
#include<QGraphicsView>
#include<QPixmap>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include "grabcut.h"
#include "grabcut2.h"

namespace Ui {
class GrabCutWindow;
}

class GrabCutWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GrabCutWindow(QWidget *parent = nullptr);
    ~GrabCutWindow();
    cv::Mat QImageToMat(const QImage &image);
    QImage image;

private slots:
    void on_loadButton_clicked();

    void on_runButton_clicked();
    void on_loadbutton2_clicked();

    void on_runbutton2_clicked();

private:
    Ui::GrabCutWindow *ui;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmapItem;
    Grabcut grabcutObject;
    Grabcut2 grabcut2Object;
};

#endif // GRABCUTWINDOW_H
