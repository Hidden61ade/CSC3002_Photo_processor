#include "nodeconnection.h"

NodeConnection::NodeConnection(void *upstream, void *downstream, bool isVariant)
{
    this->upstream = upstream;
    this->downstream = downstream;
    this->isVariant = isVariant;
    if(isVariant){
        ((Port<QVariant>*)downstream)->upstreamConnection = this;
    }else{
        ((Port<QImage>*)downstream)->upstreamConnection = this;
    }
}
NodeConnection::~NodeConnection()
{

}
void NodeConnection::ConnectData(){
    if(isVariant){
        ((Port<QVariant>*)downstream)->SetData(((Port<QVariant>*)upstream)->GetData());
        return;
    }else{
        ((Port<QImage>*)downstream)->SetData(((Port<QImage>*)upstream)->GetData());
    }
}
