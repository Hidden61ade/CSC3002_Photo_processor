#include "pipeline.h"
#include <iostream>

Pipeline::Pipeline(QObject *parent) : QObject(parent)
{

}
Pipeline* Pipeline::only = new Pipeline(nullptr);

Pipeline& Pipeline::GetInstance(){
    return *only;
}
void Pipeline::TestDoSth()
{
    std::cout << "something todo" << std::endl;
}
void Pipeline::AddNode(NodeBase &node){
    only->m_nodes.push_front(node);
    std::cout << "Node added" << std::endl;
}
void Pipeline::RemoveNode(NodeBase &node){
    only->m_nodes.remove(node);
}
