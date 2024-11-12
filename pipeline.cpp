#include "pipeline.h"

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

