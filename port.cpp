#include "port.h"
template<typename T> T &Port<T>::GetData(){}
template<typename T> void Port<T>::SetData(T &){};
template<typename T> Port<T>::~Port(){};

void VariantPort::SetData(QVariant &arg){
    delete this->data;
    this->data = new QVariant(arg);
}
QVariant &VariantPort::GetData(){
    return *data;
}
void ImagePort::SetData(QImage &arg){
    delete this->data;
    this->data = new QImage(arg);
}
QImage &ImagePort::GetData(){
    return *data;
}
