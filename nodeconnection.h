#ifndef NODECONNECTION_H
#define NODECONNECTION_H

#include "port.h"
class NodeConnection
{
public:
    NodeConnection(void *upstream, void *downstream, bool isVariant);
    ~NodeConnection();
    void ConnectData();
    bool isVariant;
private:
    void *upstream; //Dont do this
    void *downstream;
};

#endif // NODECONNECTION_H
