#include "Nodes.h"
IntNode::IntNode():NodeBase(){
    this->output0 = new VariantPort();
}
IntNode::~IntNode(){
    delete this->output0;
}
void IntNode::SetValue(int value){
    QVariant t = value;
    this->output0->SetData(t);
}

