#ifndef NODEBASE_H
#define NODEBASE_H
#include <QObject>

class NodeBase
{
public:
    NodeBase();
    NodeBase(const NodeBase& nodebase);
    virtual ~NodeBase();
    virtual void Execute();

    bool operator==(const NodeBase &other) const{
        return this==&other;
    }
};

#endif // NODEBASE_H
