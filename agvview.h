#ifndef AGVVIEW_H
#define AGVVIEW_H
#include <QGraphicsView>
#include <QLabel>
class AgvView : public QGraphicsView
{
public:
    AgvView();
    QLabel *scenePointDisPlay = new QLabel;
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    QPointF scenePoint;
};

#endif // AGVVIEW_H
