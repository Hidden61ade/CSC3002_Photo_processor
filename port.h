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
class NodeBase;
class NodeParented{
public:
    virtual NodeBase* GetParent();
protected:
    NodeBase *parent;
};

template<typename T>
class Port : public NodeParented{
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
    VariantPort(NodeBase* parent);
    void SetData(QVariant *arg) override;
    QVariant *GetData() override;
//    ~VariantPort();
    bool IsVariant() override;
    NodeBase* GetParent() override;
private:
    QVariant *data = nullptr;
};

class ImagePort : public Port<QImage>
{
public:
    ImagePort(NodeBase* parent);
    void SetData(QImage *arg) override;
    QImage *GetData() override;
//    ~ImagePort();
    bool IsVariant() override;
    NodeBase* GetParent() override;
private:
    QImage *data = nullptr;
};
#endif // PORT_H
