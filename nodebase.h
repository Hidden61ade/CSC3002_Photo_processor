#ifndef NODEBASE_H
#define NODEBASE_H
#include <QObject>

class NodeBase : public QObject
{
    Q_OBJECT
public:
    explicit NodeBase(QObject *parent = nullptr);

signals:

};

#endif // NODEBASE_H
