#include "nodebase.h"
#include "port.h"
#include "nodeconnection.h"

#ifndef NODES_H
#define NODES_H
//Nodes for pure math
class IntNode : public NodeBase{
public:
    IntNode();
    ~IntNode();
    void SetValue(int value);
    Port<QVariant> *output0 = nullptr;
};

class DoubleNode : public NodeBase
{
public:
    DoubleNode();
    ~DoubleNode();
    void SetValue(float value);
    void SetValue(double value);
    Port<QVariant> *output0 = nullptr;
};

class AddNode : public NodeBase{
public:
    AddNode();
    ~AddNode();
    void Execute() override;

    Port<QVariant> *output0 = nullptr;

    Port<QVariant> *input0 = nullptr;
    Port<QVariant> *input1 = nullptr;
    void ReqExecute(void(func0(NodeBase*))) override;
};
//Image Related
class ImageNode : public NodeBase{
public:
    ImageNode();
    ~ImageNode();
    void SetValue(QImage* arg);
    Port<QImage>* output0 = nullptr;
};
#endif // NODES_H
