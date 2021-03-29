#include "graphicscene.h"

#include <QVector4D>

GraphicScene::GraphicScene(QObject *parent) : QGraphicsScene(parent)
{
    const QPen &pen = QPen();
    const QBrush &brush = QBrush();
    addRect(300.0, 100.0, 100.0, 50.0, pen, brush);
    addRect(300.0, 500.0, 100.0, 50.0, pen, brush);
    connectionArea.push_back(QVector4D(300, 100, 400, 150));
    connectionArea.push_back(QVector4D(300, 500, 400, 550));
}

GraphicScene::~GraphicScene()
{

}

void GraphicScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!isStartPaintLine){
            if (!isConnectArea(event))
                return;
            previousPoint = event->scenePos();
            isStartPaintLine = true;
    }

    else{
            addLine(previousPoint.x(),
                        previousPoint.y(),
                        event->scenePos().x(),
                        event->scenePos().y(),
                        QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap));
            previousPoint = event->scenePos();

            if (isConnectArea(event))
                isStartPaintLine = false;
    }

}

bool GraphicScene::isConnectArea(QGraphicsSceneMouseEvent *event){
    for (int i=0; i<connectionArea.size(); i++){
        if (connectionArea[i].x() < event->scenePos().x() && connectionArea[i].y() < event->scenePos().y() && connectionArea[i].z() > event->scenePos().x() && connectionArea[i].w() > event->scenePos().y()){
            return true;
        }
    }
    return false;
}
