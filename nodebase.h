#ifndef NODEBASE_H
#define NODEBASE_H
#include <QObject>
#include "port.h"

class NodeBase
{
public:
    NodeBase();
    NodeBase(const NodeBase& nodebase);




    bool operator==(const NodeBase &other) const{
        return this==&other;
    }
};

#endif // NODEBASE_H
