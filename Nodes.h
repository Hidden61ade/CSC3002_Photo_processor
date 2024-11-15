#include "nodebase.h"
#include "port.h"

#ifndef NODES_H
#define NODES_H
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
//    void* inports[2] = {this->input0->upstreamConnection,this->input1->upstreamConnection};
};

#endif // NODES_H
