#include "lassowindow.h"
#include "ui_lassowindow.h"

LassoWindow::LassoWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LassoWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    view = ui->graphicsView;
    view->setScene(scene);
}

LassoWindow::~LassoWindow()
{
    delete ui;
    delete pixmapItem;
}

QString lassoFileName;
void LassoWindow::on_loadButton_clicked()
{
    lassoFileName = QFileDialog::getOpenFileName(this, "Choose Photo",
                                                     QCoreApplication::applicationFilePath(),
                                                     "*jpg");
    if (lassoFileName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a photo");
}else {
        image.load(lassoFileName);
        scene->clear();

        QPixmap pixmap(lassoFileName);
        pixmapItem = new QGraphicsPixmapItem(pixmap);
        scene->addItem(pixmapItem);

        view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
        view->show();
}


}

void LassoWindow::on_runButton_clicked()
{
    lassoObject.set_image(lassoFileName.toStdString());
    lassoObject.start();
}
