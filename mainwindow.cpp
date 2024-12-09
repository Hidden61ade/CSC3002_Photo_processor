#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_ImageProcessorButton_clicked()
{
    ImageProcessorWindow *I=new ImageProcessorWindow();
    I->show();
}

void MainWindow::on_grabCutButton_clicked()
{
    GrabCutWindow * G=new GrabCutWindow();
    G->show();
}

void MainWindow::on_LassoButton_clicked()
{
    LassoWindow *L=new LassoWindow();
    L->show();
}
