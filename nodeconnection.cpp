#include "nodeconnection.h"

NodeConnection::NodeConnection(void *upstream, void *downstream, bool isVariant)
{
    this->upstream = upstream;
    this->downstream = downstream;
    this->isVariant = isVariant;
    if(isVariant){
        ((Port<QVariant>*)upstream)->streamConnection = this;
        ((Port<QVariant>*)downstream)->streamConnection = this;
    }else{
        ((Port<QImage>*)upstream)->streamConnection = this;
        ((Port<QImage>*)downstream)->streamConnection = this;
    }
}
NodeConnection::~NodeConnection()
{
    if(isVariant){
        ((Port<QVariant>*)upstream)->streamConnection = nullptr;
        ((Port<QVariant>*)downstream)->streamConnection = nullptr;
    }else{
        ((Port<QImage>*)upstream)->streamConnection = nullptr;
        ((Port<QImage>*)downstream)->streamConnection = nullptr;
    }
}
void NodeConnection::ConnectData(){
    if(isVariant){
        ((Port<QVariant>*)downstream)->SetData(((Port<QVariant>*)upstream)->GetData());
        return;
    }else{
        ((Port<QImage>*)downstream)->SetData(((Port<QImage>*)upstream)->GetData());
    }
}
