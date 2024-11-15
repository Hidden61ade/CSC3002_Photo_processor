#include "nodebase.h"

#include <iostream>

NodeBase::NodeBase()
{
    std::cout << "Node created" << std::endl;
}
NodeBase::NodeBase(const NodeBase&){

}
NodeBase::~NodeBase(){};
void NodeBase::Execute(){};
void NodeBase::ReqExecute(void(func0(NodeBase*))){};
