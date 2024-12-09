#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imageprocessorwindow.h"
#include "grabcutwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ImageProcessorButton_clicked();

    void on_grabCutButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
