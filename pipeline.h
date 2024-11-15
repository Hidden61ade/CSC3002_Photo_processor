#ifndef PIPELINE_H
#define PIPELINE_H

#include <QObject>
#include <stack>
#include <iostream>
#include "nodebase.h"
#include "Nodes.h"
#include "nodeconnection.h"
class Pipeline : public QObject
{
    Q_OBJECT
//Singleton Definition
public:
    explicit Pipeline(QObject *parent = nullptr);
    static Pipeline& GetInstance();
private:
    Pipeline();
    static Pipeline *only;


//Implementation
public:
    void TestDoSth();

    NodeConnection *AddConnection(void *PortA, void *PortB, bool isVariant);

    void Execute();
    void Execute(NodeBase* arg);
    static void StackAdd(NodeBase *node);

private:
    std::stack<NodeBase*> m_nodes;
//Signal & Slots
signals:
    void OnNewConnectionAdded();
};

#endif // PIPELINE_H
