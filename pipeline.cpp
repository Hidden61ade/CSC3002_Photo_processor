#include "pipeline.h"
#include <iostream>

Pipeline::Pipeline(QObject *parent) : QObject(parent)
{

}
Pipeline* Pipeline::only = new Pipeline(nullptr);

Pipeline& Pipeline::GetInstance(){
    return *only;
}

void Pipeline::AddNode(NodeBase &node){
    only->m_nodes.push_front(node);
    std::cout << "Node added" << std::endl;
}
void Pipeline::RemoveNode(NodeBase &node){
    only->m_nodes.remove(node);
    std::cout << "Node removed" << std::endl;
}

void Pipeline::AddConnection(void *a, void *b, bool isVariant)
{
    NodeConnection *n = new NodeConnection(a,b,isVariant);
    n->ConnectData();
}

void Pipeline::TestDoSth()
{
    std::cout << "something todo" << std::endl;
}
