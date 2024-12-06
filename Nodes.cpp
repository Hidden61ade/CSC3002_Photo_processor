#include "Nodes.h"
IntNode::IntNode():NodeBase(){
    this->output0 = new VariantPort(this);
    QVariant t = 0;
    output0->SetData(&t);
}
IntNode::~IntNode(){
    delete this->output0;
}
void IntNode::SetValue(int value){
    QVariant t = value;
    this->output0->SetData(&t);
}

DoubleNode::DoubleNode(){
    this->output0 = new VariantPort(this);
    QVariant t = 0.0;
    output0->SetData(&t);
}
DoubleNode::~DoubleNode(){
    delete this->output0;
}
void DoubleNode::SetValue(float value){
    QVariant t = (double)value;
    this->output0->SetData(&t);
}
void DoubleNode::SetValue(double value){
    QVariant t = value;
    this->output0->SetData(&t);
}

AddNode::AddNode():NodeBase(){
    this->input0 = new VariantPort(this);
    this->input1 = new VariantPort(this);
    this->output0 = new VariantPort(this);
}
AddNode::~AddNode(){
    delete this->output0->streamConnection;
    delete this->input0->streamConnection;
    delete this->input1->streamConnection;
    delete this->output0;
    delete this->input0;
    delete this->input1;
}
void AddNode::Execute(){
    //Initialize 0 for input port without connection
    if(input0->streamConnection!=nullptr){
    input0->streamConnection->ConnectData();
    }else{
        QVariant t = 0;
        input0->SetData(&t);
    }
    if(input1->streamConnection!=nullptr){
    input1->streamConnection->ConnectData();
    }else{
        QVariant t = 0;
        input1->SetData(&t);
    }
    QVariant a = *input0->GetData();
    QVariant b = *input1->GetData();

//    if(a.type()!=b.type()) return;

    if(a.type()==QVariant::Double||b.type()==QVariant::Double){
        QVariant t = a.toDouble()+b.toDouble();
        output0->SetData(&t);
    }else if(a.type()==QVariant::Int&&b.type()==QVariant::Int){
        QVariant t = a.toInt()+b.toInt();
        output0->SetData(&t);
    }
}
void AddNode::ReqExecute(void(func0(NodeBase*))){
    func0(this);
    if(input0->streamConnection!=nullptr){
    reinterpret_cast<NodeParented*>(input0->streamConnection->upstream)->GetParent()->ReqExecute(func0);
    }
    if(input1->streamConnection!=nullptr){
    reinterpret_cast<NodeParented*>(input1->streamConnection->upstream)->GetParent()->ReqExecute(func0);
    }
}

ImageNode::ImageNode():NodeBase(){
    this->output0 = new ImagePort(this);
}
ImageNode::~ImageNode(){
    delete this->output0->streamConnection;
    delete this->output0;
}
void ImageNode::SetValue(QImage* arg){
    this->output0->SetData(arg);
}

VariantPassNode::VariantPassNode(){
    this->input0=new VariantPort(this);
    this->output0=new VariantPort(this);
}
VariantPassNode::~VariantPassNode(){
    delete input0->streamConnection;
    delete output0->streamConnection;
    delete input0;
    delete output0;
}
void VariantPassNode::Execute(){
    if(input0->streamConnection!=nullptr){
        input0->streamConnection->ConnectData();
    }else{
        QVariant t = 0.0;
        this->output0->SetData(&t);
        return;
    }
    output0->SetData(input0->GetData());
}
void VariantPassNode::ReqExecute(void (*func0)(NodeBase *)){
    func0(this);
    if(input0->streamConnection!=nullptr){
        reinterpret_cast<NodeParented*>(input0->streamConnection->upstream)->GetParent()->ReqExecute(func0);
    }
}

ImagePassNode::ImagePassNode(){
    input0 = new ImagePort(this);
    output0 = new ImagePort(this);
};
ImagePassNode::~ImagePassNode(){
    delete this->input0->streamConnection;
    delete this->input0;
    delete this->output0->streamConnection;
    delete this->output0;
};
void ImagePassNode::Execute(){
    if(input0->streamConnection!=nullptr){
        input0->streamConnection->ConnectData();
    }else{
        this->output0->SetData(nullptr);
        qWarning("No valid input for passing node");
        return;
    }
    output0->SetData(input0->GetData());
}
void ImagePassNode::ReqExecute(void (*func0)(NodeBase *)){
    func0(this);
    if(input0->streamConnection!=nullptr){
        reinterpret_cast<NodeParented*>(input0->streamConnection->upstream)->GetParent()->ReqExecute(func0);
    }
}

SamplerNode::SamplerNode(){
    this->output0 = new ImagePort(this);
};
SamplerNode::~SamplerNode(){
    delete this->output0->streamConnection;
    delete this->output0;
};
void SamplerNode::SetValue(QString arg){
    QImage a;
    if(a.load(arg)){
        output0->SetData(&a);
    }
};

//Color Node
ColorNode::ColorNode(){
    this->output0 = new VariantPort(this);
};
ColorNode::~ColorNode(){
    delete this->output0->streamConnection;
    delete this->output0;
};
void ColorNode::SetValue(int arg[3]){
    QVariant temp = QVector3D(arg[0],arg[1],arg[2]);
    output0->SetData(&temp);
};
void ColorNode::SetValue(QRgb arg){
    QVariant temp = QVector3D(qRed(arg),qGreen(arg),qBlue(arg));
    output0->SetData(&temp);
};

//Pixel Compute
PixelCompute::PixelCompute() {
    input0 = new ImagePort(this);
    input1 = new VariantPort(this);
    output0 = new ImagePort(this);
}
PixelCompute::~PixelCompute() {
    delete input0->streamConnection;
    delete input0;
    delete input1->streamConnection;
    delete input1;
    delete output0->streamConnection;
    delete output0;
}
void PixelCompute::Execute() {
    if (!input0 || !input0->GetData()) {
        qWarning("Input0 is null or has no data");
        return;
    }
    QImage *inputImage = input0->GetData();
    if (inputImage->isNull()) {
        qWarning("Input image is null");
        return;
    }
    QVariant argument = (input1->GetData()!=nullptr) ? *input1->GetData() : QVariant();
    QImage resultImage = inputImage->copy();
    for (int y = 0; y < resultImage.height(); ++y) {
        for (int x = 0; x < resultImage.width(); ++x) {
            QRgb pixel = resultImage.pixel(x, y);
            QRgb processedPixel = OnPixelProcess(pixel, argument);  // 调用子类实现的像素处理逻辑
            resultImage.setPixel(x, y, processedPixel);
        }
    }
    if (output0) {
        output0->SetData(&resultImage);
    }
}
QRgb PixelCompute::OnPixelProcess(QRgb rgb, QVariant arg) {
    return rgb;
}
void PixelCompute::ReqExecute(void ((*func0)(NodeBase *))){
    func0(this);
    if(input0->streamConnection!=nullptr){
    reinterpret_cast<NodeParented*>(input0->streamConnection->upstream)->GetParent()->ReqExecute(func0);
    }
    if(input1->streamConnection!=nullptr){
    reinterpret_cast<NodeParented*>(input1->streamConnection->upstream)->GetParent()->ReqExecute(func0);
    }
}

QRgb ColorMultiply::OnPixelProcess(QRgb rgb, QVariant arg) {
    if(arg.type()==QVariant::Invalid){
        return rgb;
    }
    if (arg.type() == QVariant::Vector3D) {
        QVector3D vector = arg.value<QVector3D>();
        int r = qRed(rgb) * vector.x()/255;
        int g = qGreen(rgb) * vector.y()/255;
        int b = qBlue(rgb) * vector.z()/255;
        return qRgb(qBound(0, r, 255), qBound(0, g, 255), qBound(0, b, 255));
    } else if (arg.type() == QVariant::Double) {
        double multiplier = arg.toDouble();
        int r = qRed(rgb) * multiplier;
        int g = qGreen(rgb) * multiplier;
        int b = qBlue(rgb) * multiplier;
        return qRgb(qBound(0, r, 255), qBound(0, g, 255), qBound(0, b, 255));
    }
    return rgb;
}

