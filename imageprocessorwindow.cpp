#include "imageprocessorwindow.h"
#include "ui_imageprocessorwindow.h"
#include "ImageProcessor.h"
#include <memory>
#include <QMenu>
#include <QFileDialog>
#include <QSlider>

#include <iostream>

class ImageProcessorGUIController
{
public:
    static ImageProcessorGUIController& GetInstance(){
        return *only;
    }
private:
    ImageProcessorGUIController(){
        this->imgProcessor = new ImageProcessor();
    };
    ~ImageProcessorGUIController(){
        delete this->imgProcessor;
    };
    static ImageProcessorGUIController* only;
public:
    int mode = -1;
    ImageProcessor *imgProcessor;
    QGraphicsScene *currentScene = nullptr;
    QImage *procImage = nullptr;
    QImage *copImg = nullptr;
    int paras[14];
    bool haveSaved = true;

    void Process(int brightness,
                 qreal saturationFactor,
                 qreal vibranceFactor,
                 qreal contrastFactor,
                 qreal clarityFactor,
                 qreal highlightsFactor,
                 qreal shadowsFactor,
                 qreal temperature,
                 qreal hueAmount,
                 int featherRadius,
                 qreal grainIntensity,
                 qreal whiteBalanceRed,
                 qreal whiteBalanceGreen,
                 qreal whiteBalanceBlue){
        imgProcessor->adjustImageParameters(*procImage,
                                            brightness,
                                            saturationFactor,
                                            vibranceFactor,
                                            contrastFactor,
                                            clarityFactor,
                                            highlightsFactor,
                                            shadowsFactor,
                                            temperature,
                                            hueAmount,
                                            featherRadius,
                                            grainIntensity,
                                            whiteBalanceRed,
                                            whiteBalanceGreen,
                                            whiteBalanceBlue);
    }
    void Initialize(){
        mode = -1;
        for(int i = 0; i < 14; i++){
            paras[i] = 0;
        }
        delete currentScene;
        currentScene = nullptr;
        delete procImage;
        procImage = nullptr;
        delete copImg;
        copImg = nullptr;
        haveSaved = true;
    }
    void ShowImage(QGraphicsView* target,QObject *parent){
        if(currentScene!=nullptr){
            delete currentScene;
        }
        if(copImg==nullptr){
            copImg = new QImage(*procImage);
        }
        ImageProcessorGUIController::GetInstance().haveSaved = false;
        ImageProcessorGUIController::GetInstance().currentScene = new QGraphicsScene(parent);
        ImageProcessorGUIController::GetInstance().currentScene->setSceneRect(ImageProcessorGUIController::GetInstance().copImg->rect());
        QPixmap pixmap = QPixmap::fromImage(*ImageProcessorGUIController::GetInstance().copImg);
        ImageProcessorGUIController::GetInstance().currentScene->addPixmap(pixmap);
        target->setScene(ImageProcessorGUIController::GetInstance().currentScene);
        target->fitInView(target->sceneRect(), Qt::KeepAspectRatio);
    }
};
ImageProcessorGUIController* ImageProcessorGUIController::only = new ImageProcessorGUIController();

ImageProcessorWindow::ImageProcessorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageProcessorWindow)
{
    QMenu* menu = new QMenu(this);
    QAction* brightness = menu->addAction("Brightness");
    QAction *saturation = menu->addAction("Saturation");
    QAction *vibrance = menu->addAction("Vibrance");
    QAction *contrast = menu->addAction("Contrast");
    QAction *clarity = menu->addAction("Clarity");
    QAction *highlightnshadow = menu->addAction("Highlight&Shadow");
    QAction *temperature = menu->addAction("Temperature");
    QAction *hue = menu->addAction("Hue");
    QAction *feather = menu->addAction("Feathering");
    QAction *grain = menu->addAction("AddGrain");
    QAction *whitebalance = menu->addAction("WhiteBalance");

    connect(brightness,SIGNAL(triggered()),this,SLOT(onBrightnessProc()));
    connect(saturation,SIGNAL(triggered()),this,SLOT(onSaturationProc()));
    connect(vibrance,SIGNAL(triggered()),this,SLOT(onVibranceProc()));
    connect(contrast,SIGNAL(triggered()),this,SLOT(onContrastProc()));
    connect(clarity,SIGNAL(triggered()),this,SLOT(onClarityProc()));
    connect(highlightnshadow,SIGNAL(triggered()),this,SLOT(onHighlightShadowProc()));
    connect(temperature,SIGNAL(triggered()),this,SLOT(onTemperatureProc()));
    connect(hue,SIGNAL(triggered()),this,SLOT(onHueProc()));
    connect(feather,SIGNAL(triggered()),this,SLOT(featherEdgesProc()));
    connect(grain,SIGNAL(triggered()),this,SLOT(addGainProc()));
    connect(whitebalance,SIGNAL(triggered()),this,SLOT(whiteBalanceProc()));

    ui->setupUi(this);
    ui->pushButton_2->setMenu(menu);
}
ImageProcessorWindow::~ImageProcessorWindow()
{
    delete ui;
}
void ImageProcessorWindow::SetParaValue(int value){
    if(ImageProcessorGUIController::GetInstance().mode==0){
    ImageProcessorGUIController::GetInstance().paras[0] = value;
    }else {

    }
}
void ImageProcessorWindow::on_LoadButton_clicked()
{
    if(!ImageProcessorGUIController::GetInstance().haveSaved){
        //TODO:提示未保存
        std::cout << "YOU DIDNT SAVE!!" << std::endl;
    }
    changeState(-1);
    ImageProcessorGUIController::GetInstance().Initialize();
    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("File (*.bmp)"));
    if(filename.toStdString()==""){
        return;
    }
    std::cout << "Loaded: " <<filename.toStdString() << std::endl;
    if(ImageProcessorGUIController::GetInstance().procImage!=nullptr){
        delete ImageProcessorGUIController::GetInstance().procImage;
    }
    ImageProcessorGUIController::GetInstance().procImage = new QImage;
    if(ImageProcessorGUIController::GetInstance().procImage->load(filename)){
        ImageProcessorGUIController::GetInstance().ShowImage(ui->graphicsView,this);
    }else{
        std::cout << "An Unknow Problem Happened." << std::endl;
    }
}

void ImageProcessorWindow::on_SaveButton_clicked()
{

}

void ImageProcessorWindow::on_pushButton_2_clicked()
{

}
void ImageProcessorWindow::changeState(int i){
    while(ui->verticalLayout->count())
    {
         QWidget *p=this->ui->verticalLayout->itemAt(0)->widget();
         p->setParent (NULL);
         this->ui->verticalLayout->removeWidget(p);
         delete p;
    }
    ImageProcessorGUIController::GetInstance().mode = i;
}
void ImageProcessorWindow::onBrightnessProc(){
    changeState(0);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">Brightness</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(-255);
    slider->setMaximum(255);
    slider->setValue(0);

    ui->verticalLayout->addWidget(slider);
    connect(slider, &QSlider::valueChanged, this,&ImageProcessorWindow::SetParaValue);
}
void ImageProcessorWindow::onSaturationProc(){
    changeState(1);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">Saturation</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(20);
    slider->setValue(0);

    ui->verticalLayout->addWidget(slider);
};
void ImageProcessorWindow::onVibranceProc(){
    changeState(2);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">Vibrance</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(20);
    slider->setValue(0);

    ui->verticalLayout->addWidget(slider);
};
void ImageProcessorWindow::onContrastProc(){
    changeState(3);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">Contrast</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(5);
    slider->setMaximum(30);
    slider->setValue(5);

    ui->verticalLayout->addWidget(slider);
};
void ImageProcessorWindow::onClarityProc(){
    changeState(4);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">Clarity</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(-100);
    slider->setMaximum(100);
    slider->setValue(0);

    ui->verticalLayout->addWidget(slider);
};
void ImageProcessorWindow::onHighlightShadowProc(){
    changeState(5);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">Highlight & Shadow</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(20);
    slider->setValue(0);
    QSlider* slider2(new QSlider(this));
    slider2->setOrientation(Qt::Orientation::Horizontal);
    slider2->setMinimum(0);
    slider2->setMaximum(20);
    slider2->setValue(0);
    ui->verticalLayout->addWidget(slider);
    ui->verticalLayout->addWidget(slider2);
};
void ImageProcessorWindow::onTemperatureProc(){
    changeState(6);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">Temperature</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(-100);
    slider->setMaximum(100);
    slider->setValue(0);

    ui->verticalLayout->addWidget(slider);
};
void ImageProcessorWindow::onHueProc(){
    changeState(7);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">Hue</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(-180);
    slider->setMaximum(180);
    slider->setValue(0);

    ui->verticalLayout->addWidget(slider);
};
void ImageProcessorWindow::featherEdgesProc(){
    changeState(8);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">Feathering</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(50);
    slider->setValue(0);

    ui->verticalLayout->addWidget(slider);
};
void ImageProcessorWindow::addGainProc(){
    changeState(9);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">Grain</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(10);
    slider->setValue(0);

    ui->verticalLayout->addWidget(slider);
};
void ImageProcessorWindow::whiteBalanceProc(){
    changeState(10);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">White Balance</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(5);
    slider->setMaximum(20);
    slider->setValue(0);

    QSlider* slider1(new QSlider(this));
    slider1->setOrientation(Qt::Orientation::Horizontal);
    slider1->setMinimum(5);
    slider1->setMaximum(20);
    slider1->setValue(0);

    QSlider* slider2(new QSlider(this));
    slider2->setOrientation(Qt::Orientation::Horizontal);
    slider2->setMinimum(5);
    slider2->setMaximum(20);
    slider2->setValue(0);

    ui->verticalLayout->addWidget(slider);
    ui->verticalLayout->addWidget(slider1);
    ui->verticalLayout->addWidget(slider2);
};


//Process
void ImageProcessorWindow::on_pushButton_pressed()
{
    if(ImageProcessorGUIController::GetInstance().procImage==nullptr){
        return;
    }
    ImageProcessorGUIController::GetInstance().copImg = new QImage(*ImageProcessorGUIController::GetInstance().procImage);
    ImageProcessorGUIController::GetInstance().imgProcessor->adjustBrightness(
        *ImageProcessorGUIController::GetInstance().copImg,
        ImageProcessorGUIController::GetInstance().paras[0]
    );
    ImageProcessorGUIController::GetInstance().ShowImage(ui->graphicsView,this);
}
