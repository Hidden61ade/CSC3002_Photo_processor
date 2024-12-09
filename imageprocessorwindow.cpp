#include "imageprocessorwindow.h"
#include "ui_imageprocessorwindow.h"
#include "ImageProcessor.h"
#include <memory>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <QSlider>
#include <cstring>

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
    int initParas[14] = {0,10,10,10,0,10,10,0,0,0,0,10,10,10};
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
        imgProcessor->adjustImageParameters(*copImg,
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
        memcpy(paras,initParas,14*sizeof(int));
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
    int t = ImageProcessorGUIController::GetInstance().mode;
    if(t==0){
        ImageProcessorGUIController::GetInstance().paras[0] = value;
    }else if(t==1){
        ImageProcessorGUIController::GetInstance().paras[1] = value;
    }else if(t==2){
        ImageProcessorGUIController::GetInstance().paras[2] = value;
    }else if(t==3){
        ImageProcessorGUIController::GetInstance().paras[3] = value;
    }else if(t==4){
        ImageProcessorGUIController::GetInstance().paras[4] = value;
    }else if(t==6){
        ImageProcessorGUIController::GetInstance().paras[7] = value;
    }else if(t==7){
        ImageProcessorGUIController::GetInstance().paras[8] = value;
    }else if(t==8){
        ImageProcessorGUIController::GetInstance().paras[9] = value;
    }else if(t==9){
        ImageProcessorGUIController::GetInstance().paras[10] = value;
    }
}
void ImageProcessorWindow::SetH(int value){
    ImageProcessorGUIController::GetInstance().paras[5] = value;
}
void ImageProcessorWindow::SetS(int value){
    ImageProcessorGUIController::GetInstance().paras[6] = value;
}
void ImageProcessorWindow::SetR(int value){
    ImageProcessorGUIController::GetInstance().paras[11] = value;
}
void ImageProcessorWindow::SetG(int value){
    ImageProcessorGUIController::GetInstance().paras[12] = value;
}
void ImageProcessorWindow::SetB(int value){
    ImageProcessorGUIController::GetInstance().paras[13] = value;
}

void ImageProcessorWindow::on_LoadButton_clicked()
{
    if(!ImageProcessorGUIController::GetInstance().haveSaved){
        //TODO:提示未保存
        QMessageBox::StandardButton a = QMessageBox::information(NULL, "Image Processor", "Do you want to save current change of the file?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);
        if(a==QMessageBox::StandardButton::Cancel){
            return;
        }else if (a==QMessageBox::StandardButton::Yes){
            on_SaveButton_clicked();
            return;
        }
    }
    changeState(-1);
    ImageProcessorGUIController::GetInstance().Initialize();
    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm)"));
    if(filename.toStdString()==""){
        return;
    }
    if(ImageProcessorGUIController::GetInstance().procImage!=nullptr){
        delete ImageProcessorGUIController::GetInstance().procImage;
    }
    ImageProcessorGUIController::GetInstance().procImage = new QImage;
    if(ImageProcessorGUIController::GetInstance().procImage->load(filename)){
        ImageProcessorGUIController::GetInstance().ShowImage(ui->graphicsView,this);
        this->filename = filename;
//        std::cout << "Loaded: " <<filename.toStdString() << std::endl;
    }else{
//        std::cout << "An Unknow Problem Happened." << std::endl;
    }
}

void ImageProcessorWindow::on_SaveButton_clicked()
{
    if(ImageProcessorGUIController::GetInstance().procImage==nullptr||this->filename.isEmpty()){
        return;
    }
    QString t = this->filename.left(this->filename.lastIndexOf("."));
    QString res = QFileDialog::getSaveFileName(this,tr("Save File"),t.append("(1)"),tr("BMP (*.bmp);;JPG (*.jpg);;PNG (*.png)"));
//    std::cout << res.toStdString() << std::endl;
    ImageProcessorGUIController::GetInstance().copImg->save(res);
    ImageProcessorGUIController::GetInstance().haveSaved = true;
}

void ImageProcessorWindow::on_pushButton_2_clicked()
{
    //Use menu to select mode, nothing happens here.
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
    slider->setValue(ImageProcessorGUIController::GetInstance().paras[0]);

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
    slider->setValue(ImageProcessorGUIController::GetInstance().paras[1]);

    ui->verticalLayout->addWidget(slider);
    connect(slider, &QSlider::valueChanged, this,&ImageProcessorWindow::SetParaValue);
};
void ImageProcessorWindow::onVibranceProc(){
    changeState(2);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">Vibrance</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(20);
    slider->setValue(ImageProcessorGUIController::GetInstance().paras[2]);

    ui->verticalLayout->addWidget(slider);
    connect(slider, &QSlider::valueChanged, this,&ImageProcessorWindow::SetParaValue);
};
void ImageProcessorWindow::onContrastProc(){
    changeState(3);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">Contrast</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(5);
    slider->setMaximum(30);
    slider->setValue(ImageProcessorGUIController::GetInstance().paras[3]);

    ui->verticalLayout->addWidget(slider);
    connect(slider, &QSlider::valueChanged, this,&ImageProcessorWindow::SetParaValue);
};
void ImageProcessorWindow::onClarityProc(){
    changeState(4);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">Clarity</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(-100);
    slider->setMaximum(100);
    slider->setValue(ImageProcessorGUIController::GetInstance().paras[4]);

    ui->verticalLayout->addWidget(slider);
    connect(slider, &QSlider::valueChanged, this,&ImageProcessorWindow::SetParaValue);
};
void ImageProcessorWindow::onHighlightShadowProc(){
    changeState(5);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">Highlight & Shadow</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(20);
    slider->setValue(ImageProcessorGUIController::GetInstance().paras[5]);
    QSlider* slider2(new QSlider(this));
    slider2->setOrientation(Qt::Orientation::Horizontal);
    slider2->setMinimum(0);
    slider2->setMaximum(20);
    slider2->setValue(ImageProcessorGUIController::GetInstance().paras[6]);
    ui->verticalLayout->addWidget(slider);
    ui->verticalLayout->addWidget(slider2);
    connect(slider, &QSlider::valueChanged, this,&ImageProcessorWindow::SetH);
    connect(slider2, &QSlider::valueChanged, this,&ImageProcessorWindow::SetS);
};
void ImageProcessorWindow::onTemperatureProc(){
    changeState(6);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">Temperature</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(-100);
    slider->setMaximum(100);
    slider->setValue(ImageProcessorGUIController::GetInstance().paras[7]);

    ui->verticalLayout->addWidget(slider);
    connect(slider, &QSlider::valueChanged, this,&ImageProcessorWindow::SetParaValue);
};
void ImageProcessorWindow::onHueProc(){
    changeState(7);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">Hue</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(-180);
    slider->setMaximum(180);
    slider->setValue(ImageProcessorGUIController::GetInstance().paras[8]);

    ui->verticalLayout->addWidget(slider);
    connect(slider, &QSlider::valueChanged, this,&ImageProcessorWindow::SetParaValue);
};
void ImageProcessorWindow::featherEdgesProc(){
    changeState(8);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">Feathering</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(50);
    slider->setValue(ImageProcessorGUIController::GetInstance().paras[9]);

    ui->verticalLayout->addWidget(slider);
    connect(slider, &QSlider::valueChanged, this,&ImageProcessorWindow::SetParaValue);
};
void ImageProcessorWindow::addGainProc(){
    changeState(9);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">Grain</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(10);
    slider->setValue(ImageProcessorGUIController::GetInstance().paras[10]);

    ui->verticalLayout->addWidget(slider);
    connect(slider, &QSlider::valueChanged, this,&ImageProcessorWindow::SetParaValue);
};
void ImageProcessorWindow::whiteBalanceProc(){
    changeState(10);

    ui->label_2->setText(R"(<html><head/><body><p><span style=" font-size:12pt;">White Balance</span></p></body></html>)");
    QSlider* slider(new QSlider(this));
    slider->setOrientation(Qt::Orientation::Horizontal);
    slider->setMinimum(5);
    slider->setMaximum(20);
    slider->setValue(ImageProcessorGUIController::GetInstance().paras[11]);

    QSlider* slider1(new QSlider(this));
    slider1->setOrientation(Qt::Orientation::Horizontal);
    slider1->setMinimum(5);
    slider1->setMaximum(20);
    slider1->setValue(ImageProcessorGUIController::GetInstance().paras[12]);

    QSlider* slider2(new QSlider(this));
    slider2->setOrientation(Qt::Orientation::Horizontal);
    slider2->setMinimum(5);
    slider2->setMaximum(20);
    slider2->setValue(ImageProcessorGUIController::GetInstance().paras[13]);

    ui->verticalLayout->addWidget(slider);
    ui->verticalLayout->addWidget(slider1);
    ui->verticalLayout->addWidget(slider2);
    connect(slider, &QSlider::valueChanged, this,&ImageProcessorWindow::SetR);
    connect(slider1, &QSlider::valueChanged, this,&ImageProcessorWindow::SetG);
    connect(slider2, &QSlider::valueChanged, this,&ImageProcessorWindow::SetB);
};


//Process
void ImageProcessorWindow::on_pushButton_pressed()
{
    if(ImageProcessorGUIController::GetInstance().procImage==nullptr){
        return;
    }
    delete ImageProcessorGUIController::GetInstance().copImg;
    ImageProcessorGUIController::GetInstance().copImg = new QImage(*ImageProcessorGUIController::GetInstance().procImage);
    int (&paras)[14] = ImageProcessorGUIController::GetInstance().paras;
    ImageProcessorGUIController::GetInstance().Process(
            paras[0],paras[1]/10.0f,paras[2]/10.0f,paras[3]/10.0f,paras[4],
            paras[5]/10.0f,paras[6]/10.0f,paras[7],paras[8],paras[9],
            paras[10]/10.0f,paras[11]/10.0f,paras[12]/10.0f,paras[13]/10.0f);
    ImageProcessorGUIController::GetInstance().ShowImage(ui->graphicsView,this);
}
