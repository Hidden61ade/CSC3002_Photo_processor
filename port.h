#ifndef PORT_H
#define PORT_H

#include <string>
#include <functional>
#include <QVariant>
#include <QImage>
//#include <list>

//typedef enum struct pt{
//    Sampler,
//    Tex,
//    UV,
//    Grad,
//}ParaType;

template<typename T>
class Port{
public:
    virtual void SetData(T &arg);
    virtual T &GetData();
    virtual ~Port();
};

class VariantPort : public Port<QVariant>
{
public:
    void SetData(QVariant &arg) override;
    QVariant &GetData() override;
private:
    QVariant *data = nullptr;
};

class ImagePort : public Port<QImage>
{
public:
    void SetData(QImage &arg) override;
    QImage &GetData() override;
private:
    QImage *data = nullptr;
};
#endif // PORT_H
