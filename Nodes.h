#include "nodebase.h"
#include "port.h"
#include "nodeconnection.h"
#include <QVector3D>

#ifndef NODES_H
#define NODES_H
//Nodes for pure math
class IntNode : public NodeBase{
public:
    IntNode();
    ~IntNode();
    void SetValue(int value);
    Port<QVariant> *output0 = nullptr;
};

class DoubleNode : public NodeBase
{
public:
    DoubleNode();
    ~DoubleNode();
    void SetValue(float value);
    void SetValue(double value);
    Port<QVariant> *output0 = nullptr;
};

class VariantPassNode : public NodeBase{
public:
    VariantPassNode();
    ~VariantPassNode();
    void Execute() override;
    void ReqExecute(void (*func0)(NodeBase *)) override;
    Port<QVariant> *input0 = nullptr;
    Port<QVariant> *output0 = nullptr;
};

class AddNode : public NodeBase{
public:
    AddNode();
    ~AddNode();
    void Execute() override;

    Port<QVariant> *output0 = nullptr;

    Port<QVariant> *input0 = nullptr;
    Port<QVariant> *input1 = nullptr;
    void ReqExecute(void(func0(NodeBase*))) override;
};

//Image Related
class ImageNode : public NodeBase{
public:
    ImageNode();
    ~ImageNode();
    void SetValue(QImage* arg);
    Port<QImage>* output0 = nullptr;
};
class ImagePassNode : public NodeBase{
public:
    ImagePassNode();
    ~ImagePassNode();
    void Execute() override;
    void ReqExecute(void (*func0)(NodeBase *)) override;
    Port<QImage> *input0 = nullptr;
    Port<QImage> *output0 = nullptr;
};

class SamplerNode : public NodeBase{
public:
    SamplerNode();
    ~SamplerNode();
    void SetValue(QString arg);
    Port<QImage>* output0 = nullptr;
};
class ColorNode : public NodeBase{
public:
    ColorNode();
    ~ColorNode();
    void SetValue(int arg[3]);
    void SetValue(QRgb arg);
    Port<QVariant>* output0 = nullptr;
};
class PixelCompute : public NodeBase{
public:
    PixelCompute();
    ~PixelCompute();
    void Execute() override;
    virtual QRgb OnPixelProcess(QRgb rgb, QVariant arg);
    Port<QImage> *output0 = nullptr;

    Port<QImage> *input0 = nullptr;
    Port<QVariant> *input1 = nullptr;
    void ReqExecute(void(func0(NodeBase*))) override;
};
class ColorMultiply : public PixelCompute{
public:
    QRgb OnPixelProcess(QRgb rgb, QVariant arg) override;
};
#endif // NODES_H
