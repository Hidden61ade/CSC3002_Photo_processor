#ifndef PORT_H
#define PORT_H

#include <string>
#include <functional>
#include <nodebase.h>
//#include <list>

template <typename T>
class Port
{
public:
    enum struct ParaType{
        Int,
        Bool,
        Float,
        Vec2,
        //Vec3,
        Vec4,
        //Sampler,
        //Tex,
        //UV,
        //Grad,
    };


    Port(ParaType tp, NodeBase &node);
    virtual T &GetData();
    void SetData(T &value);
    ParaType GetDataType();


private:
    ParaType m_dataType;
    NodeBase &m_baseNode;
    T m_data;
    std::function<T&(void)> m_dataExtractFunc;
};

#endif // PORT_H
