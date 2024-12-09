#include "lassowindow.h"
#include "ui_lassowindow.h"

LassoWindow::LassoWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LassoWindow)
{
    ui->setupUi(this);
}

LassoWindow::~LassoWindow()
{
    delete ui;
}
