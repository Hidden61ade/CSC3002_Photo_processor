#include "Nodes.h"
IntNode::IntNode():NodeBase(){
    this->output0 = new VariantPort();
}
IntNode::~IntNode(){
    delete this->output0;
}
void IntNode::SetValue(int value){
    QVariant t = value;
    this->output0->SetData(&t);
}

DoubleNode::DoubleNode(){
this->output0 = new VariantPort();
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
    this->input0 = new VariantPort();
    this->input1 = new VariantPort();
    this->output0 = new VariantPort();
}
AddNode::~AddNode(){
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
    if(a.type()!=b.type()) return;
    if(a.type()==QVariant::Int){
        QVariant t = a.toInt()+b.toInt();
        output0->SetData(&t);
    }else if(a.type()==QVariant::Double){
        QVariant t = a.toDouble()+b.toDouble();
        output0->SetData(&t);
    }
}
