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

namespace Ui {
class LassoWindow;
}

class LassoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LassoWindow(QWidget *parent = nullptr);
    ~LassoWindow();


private:
    Ui::LassoWindow *ui;
};

#endif // LASSOWINDOW_H
