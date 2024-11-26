#include "grabcutwindow.h"
#include "ui_grabcutwindow.h"

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
}

void GrabCutWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose Photo",
                                                     QCoreApplication::applicationFilePath(),
                                                     "*bmp");
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a photo");
    } else {

        scene->clear();

        QPixmap pixmap(fileName);
        pixmapItem = new QGraphicsPixmapItem(pixmap);
        scene->addItem(pixmapItem);

        view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
        view->show();
    }
}

