#ifndef PORT_H
#define PORT_H

#include <QVariant>
#include <QImage>

//typedef enum struct pt{
//    Sampler,
//    Tex,
//    UV,
//    Grad,
//}ParaType;
class NodeConnection;

template<typename T>
class Port{
public:
    virtual void SetData(T *arg);
    virtual T *GetData();
    virtual ~Port();
    virtual bool IsVariant();
    NodeConnection *streamConnection = nullptr;
};

class VariantPort : public Port<QVariant>
{
public:
    void SetData(QVariant *arg) override;
    QVariant *GetData() override;
//    ~VariantPort();
    bool IsVariant() override;
private:
    QVariant *data = nullptr;
};

class ImagePort : public Port<QImage>
{
public:
    void SetData(QImage *arg) override;
    QImage *GetData() override;
//    ~ImagePort();
    bool IsVariant() override;
private:
    QImage *data = nullptr;
};
#endif // PORT_H
