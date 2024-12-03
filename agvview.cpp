#include "agvview.h"
#include <QMouseEvent>
#include <QString>
AgvView::AgvView()
{

}
void AgvView::mouseMoveEvent(QMouseEvent *event){
    QPoint viewPoint = event->pos();

    scenePoint = mapToScene(viewPoint);
    setMouseTracking(true);
    this->scenePointDisPlay->setText("("+QString::number(scenePoint.x())+", "+QString::number(scenePoint.y())+")");
}
