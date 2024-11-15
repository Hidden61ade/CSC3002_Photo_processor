#include "port.h"
template<typename T> T *Port<T>::GetData(){}
template<typename T> void Port<T>::SetData(T *){};
template<typename T> Port<T>::~Port(){};
template<typename T> bool Port<T>::IsVariant(){return true;};
NodeBase* NodeParented::GetParent(){return nullptr;}


VariantPort::VariantPort(NodeBase* parent){
    this->parent = parent;
}
NodeBase* VariantPort::GetParent(){
    return this->parent;
}
void VariantPort::SetData(QVariant *arg){
    delete this->data;
    if(arg==nullptr){
        this->data = nullptr;
        return;
    }
    this->data = new QVariant(*arg);
}
QVariant *VariantPort::GetData(){
    return data;
}
bool VariantPort::IsVariant(){
    return true;
}

ImagePort::ImagePort(NodeBase* parent){
    this->parent = parent;
}
NodeBase* ImagePort::GetParent(){
    return this->parent;
}
void ImagePort::SetData(QImage *arg){
    delete this->data;
    if(arg==nullptr){
        this->data = nullptr;
        return;
    }
    this->data = new QImage(*arg);
}
QImage *ImagePort::GetData(){
    return data;
}
bool ImagePort::IsVariant(){
    return false;
}
