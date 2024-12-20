﻿#include "grabcutwindow.h"
#include "ui_grabcutwindow.h"

#include <iostream>

cv::Mat GrabCutWindow::QImageToMat(const QImage &image) {
    if (image.format() != QImage::Format_RGB888) {
        const QImage &convertedImage = image.convertToFormat(QImage::Format_RGB888);
        return cv::Mat(convertedImage.height(), convertedImage.width(), CV_8UC3, (void*)convertedImage.bits(), convertedImage.bytesPerLine());
    }
    return cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.bits(), image.bytesPerLine());
}

GrabCutWindow::GrabCutWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GrabCutWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    view = ui->graphicsView;
    view->setScene(scene);
}

GrabCutWindow::~GrabCutWindow()
{
    delete ui;
    delete pixmapItem;
}
QString fileName;
void GrabCutWindow::on_loadButton_clicked()
{

    fileName = QFileDialog::getOpenFileName(this, "Choose Photo",
                                                     QCoreApplication::applicationFilePath(),
                                                     "*jpg");
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a photo");
    } else {
        image.load(fileName);
        scene->clear();

        QPixmap pixmap(fileName);
        pixmapItem = new QGraphicsPixmapItem(pixmap);
        scene->addItem(pixmapItem);

        view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
        view->show();
    }
}


void GrabCutWindow::on_runButton_clicked()
{
    QString x1 =ui->x1LineEdit->text();
    QString y1 =ui->y1LineEdit->text();
    QString x2 =ui->x2lineEdit->text();
    QString y2 =ui->y2LineEdit->text();
    grabcutObject.set_rectangle(x1.toInt(),y1.toInt(),x2.toInt(),y2.toInt());
    cv::Mat cvImage = cv::imread(fileName.toStdString());
    grabcutObject.set_image(cvImage);
    grabcutObject.runGrabcut();
}

QString fileName2;
void GrabCutWindow::on_loadbutton2_clicked()
{
    fileName2 = QFileDialog::getOpenFileName(this, "Choose Photo2",
                                                     QCoreApplication::applicationFilePath(),
                                                     "*jpg");
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a photo");
}
}

void GrabCutWindow::on_runbutton2_clicked()
{
    QString x1 =ui->x1LineEdit->text();
    QString y1 =ui->y1LineEdit->text();
    QString x2 =ui->x2lineEdit->text();
    QString y2 =ui->y2LineEdit->text();
    grabcut2Object.set_rectangle(x1.toInt(),y1.toInt(),x2.toInt(),y2.toInt());
    cv::Mat cvImage = cv::imread(fileName.toStdString());
    cv::Mat cvImage2 = cv::imread(fileName2.toStdString());
    grabcut2Object.set_image(cvImage,cvImage2);
    grabcut2Object.runGrabcut();
}
