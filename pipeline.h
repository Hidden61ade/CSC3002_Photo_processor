#ifndef PIPELINE_H
#define PIPELINE_H

#include <QObject>
#include <list>
#include <iostream>
#include <port.h>

class Pipeline : public QObject
{
    Q_OBJECT
//Singleton Definition
public:
    explicit Pipeline(QObject *parent = nullptr);
    static Pipeline& GetInstance();
private:
    Pipeline();
    static Pipeline *only;


//Implementation
public:
    void TestDoSth();
    template<typename T> bool AddConnection(Port<T> &a, Port<T> &b);

//Signal & Slots
signals:
    void OnNewConnectionAdded();
};

#endif // PIPELINE_H
