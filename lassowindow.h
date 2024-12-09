#ifndef LASSOWINDOW_H
#define LASSOWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QFileDialog>
#include<QString>
#include<QMessageBox>
#include<QGraphicsView>
#include<QPixmap>
#include <QGraphicsPixmapItem>
#include <lasso.h>

namespace Ui {
class LassoWindow;
}

class LassoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LassoWindow(QWidget *parent = nullptr);
    ~LassoWindow();


private slots:
    void on_loadButton_clicked();

    void on_runButton_clicked();

private:
    Ui::LassoWindow *ui;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmapItem;
    Lasso lassoObject;
    QImage image;

};

#endif // LASSOWINDOW_H
