#include "nodebase.h"

#include <iostream>

NodeBase::NodeBase()
{
    std::cout << "Node created" << std::endl;
}
NodeBase::NodeBase(const NodeBase&){

}
void NodeBase::Execute(){};
