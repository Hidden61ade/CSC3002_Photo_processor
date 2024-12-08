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

QString fileName;
void LassoWindow::on_loadButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, "Choose Photo",
                                                     QCoreApplication::applicationFilePath(),
                                                     "*jpg");
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a photo");
}else {
        image.load(fileName);
        scene->clear();

        QPixmap pixmap(fileName);
        pixmapItem = new QGraphicsPixmapItem(pixmap);
        scene->addItem(pixmapItem);

        view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
        view->show();
}


}
