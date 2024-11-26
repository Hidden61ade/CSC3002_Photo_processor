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

namespace Ui {
class GrabCutWindow;
}

class GrabCutWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GrabCutWindow(QWidget *parent = nullptr);
    ~GrabCutWindow();

private slots:
    void on_loadButton_clicked();

private:
    Ui::GrabCutWindow *ui;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmapItem;
};

#endif // GRABCUTWINDOW_H
