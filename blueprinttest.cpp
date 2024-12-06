#include "blueprinttest.h"
#include "ui_blueprinttest.h"
#include "pipeline.h"
#include "nodebase.h"
#include "Nodes.h"

BluePrintTest::BluePrintTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BluePrintTest)
{
    ui->setupUi(this);
}

BluePrintTest::~BluePrintTest()
{
    delete ui;
}
SamplerNode *Sampler;
PixelCompute *pixNode;
ImagePassNode *output;
DoubleNode *doubleNode;
ColorNode *colorNode;
void BluePrintTest::on_pushButton_clicked()
{
    Sampler = new SamplerNode();
    Sampler->SetValue(R"(D:\m2\GitHub\CSC3002_Photo_processor\LenaRGB.bmp)");
    QPixmap preview = QPixmap::fromImage(*Sampler->output0->GetData());
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(preview);
    scene->setSceneRect(preview.rect());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(ui->graphicsView->sceneRect(),Qt::KeepAspectRatio);

    pixNode = new ColorMultiply();
    output = new ImagePassNode();
    doubleNode = new DoubleNode();
    colorNode = new ColorNode();
}

void BluePrintTest::on_pushButton_2_clicked()
{
    doubleNode->SetValue(0.5);
    int custom_color[3] = {255,100,150};
    colorNode->SetValue(custom_color);
    Pipeline::GetInstance().AddConnection(Sampler->output0,pixNode->input0,Sampler->output0->IsVariant());
    Pipeline::GetInstance().AddConnection(colorNode->output0,pixNode->input1,Sampler->output0->IsVariant());
    Pipeline::GetInstance().AddConnection(pixNode->output0,output->input0,false);
    Pipeline::GetInstance().Execute(output);


    QPixmap preview = QPixmap::fromImage(*output->output0->GetData());
    QGraphicsScene *scene = ui->graphicsView->scene();
    scene->clear();
    scene->addPixmap(preview);
    scene->setSceneRect(preview.rect());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(ui->graphicsView->sceneRect(),Qt::KeepAspectRatio);
}
