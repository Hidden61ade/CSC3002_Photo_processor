#include "pipeline.h"
#include <iostream>

Pipeline::Pipeline(QObject *parent) : QObject(parent)
{

}
Pipeline* Pipeline::only = new Pipeline(nullptr);

Pipeline& Pipeline::GetInstance(){
    return *only;
}
NodeConnection* Pipeline::AddConnection(void *a, void *b, bool isVariant)
{
    NodeConnection *n = new NodeConnection(a,b,isVariant);
    n->ConnectData();
    return n;
}
void Pipeline::StackAdd(NodeBase *node){
    only->m_nodes.push(node);
}
void Pipeline::Execute(NodeBase *arg){
    arg->ReqExecute(StackAdd);
    while(!only->m_nodes.empty()){
        m_nodes.top()->Execute();
        m_nodes.pop();
    }
}

void Pipeline::TestDoSth()
{
    std::cout << "[PIPELINE] Pipeline Singleton Test." << std::endl;
}
