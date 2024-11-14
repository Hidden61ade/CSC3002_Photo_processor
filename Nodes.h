#include "nodebase.h"
#ifndef NODES_H
#define NODES_H
class IntNode : public NodeBase{
public:
    IntNode();
    ~IntNode();
    void SetValue(int value);
    Port<QVariant> *output0 = nullptr;
};
#endif // NODES_H
