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
