#ifndef PIPELINE_H
#define PIPELINE_H

#include <QObject>
#include <list>
#include <iostream>
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

    void AddNode(NodeBase &node);
    void RemoveNode(NodeBase &node);

    NodeConnection *AddConnection(void *PortA, void *PortB, bool isVariant);

    void Execute();


private:
    std::list<NodeBase> m_nodes;
//Signal & Slots
signals:
    void OnNewConnectionAdded();
};

#endif // PIPELINE_H
