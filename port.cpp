#include "port.h"
template<typename T> Port<T>::Port(ParaType tp, NodeBase &node){
    this->m_dataType = tp;
    this->m_baseNode = node;
}
