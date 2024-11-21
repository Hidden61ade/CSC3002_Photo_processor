#include "imageprocessorwindow.h"
#include "ui_imageprocessorwindow.h"

ImageProcessorWindow::ImageProcessorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageProcessorWindow)
{
    ui->setupUi(this);
}

ImageProcessorWindow::~ImageProcessorWindow()
{
    delete ui;
}
