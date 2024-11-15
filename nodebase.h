#ifndef NODEBASE_H
#define NODEBASE_H
#include <QObject>
class NodeConnection;
class NodeBase
{
public:
    NodeBase();
    NodeBase(const NodeBase& nodebase);
    virtual ~NodeBase();
    virtual void Execute();
    virtual void ReqExecute(void(func0(NodeBase*)));
    bool operator==(const NodeBase &other) const{
        return this==&other;
    }
};

#endif // NODEBASE_H
