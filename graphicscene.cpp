#include "graphicblock.h"

GraphicScene::GraphicScene(QObject *parent) : QGraphicsScene(parent)
{

}

GraphicScene::~GraphicScene()
{

}

void GraphicScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPen pen(Qt::black);
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    if (!isStartPaintLine){
            if (!isOutputConnectArea(event)){
                drawBlock(event);
                return;
            }
            previousPoint = event->scenePos();
            addEllipse(event->scenePos().x()-5, event->scenePos().y()-5, 10, 10, pen, brush);
            isStartPaintLine = true;
    }

    else{
            addLine(previousPoint.x(),
                        previousPoint.y(),
                        event->scenePos().x(),
                        event->scenePos().y(),
                        QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap));
            previousPoint = event->scenePos();
            if (isInputConnectArea(event)){
                isStartPaintLine = false;
                QPolygonF polygon;
                polygon << QPoint(event->scenePos().x(), event->scenePos().y()+7) << QPoint(event->scenePos().x()-7, event->scenePos().y()) << QPoint(event->scenePos().x(), event->scenePos().y()-7) << QPoint(event->scenePos().x()+7, event->scenePos().y());
                addPolygon(polygon, pen, brush);
            }
    }



}

void GraphicScene::drawBlock(QGraphicsSceneMouseEvent *event){

    Graphicblock block = Graphicblock::createBlock(buttonType, event);
    block.draw(this);

}

void GraphicScene::setButtonType(const ButtonType &value)
{
    buttonType = value;
}

bool GraphicScene::isInputConnectArea(QGraphicsSceneMouseEvent *event){
    for (int i=0; i<inputConnectionArea.size(); i++){
        if (inputConnectionArea[i].x() < event->scenePos().x() && inputConnectionArea[i].y() < event->scenePos().y() && inputConnectionArea[i].z() > event->scenePos().x() && inputConnectionArea[i].w() > event->scenePos().y()){
            return true;
        }
    }
    return false;
}

bool GraphicScene::isOutputConnectArea(QGraphicsSceneMouseEvent *event){
    for (int i=0; i<outputConnectionArea.size(); i++){
        if (outputConnectionArea[i].x() < event->scenePos().x() && outputConnectionArea[i].y() < event->scenePos().y() && outputConnectionArea[i].z() > event->scenePos().x() && outputConnectionArea[i].w() > event->scenePos().y()){
            return true;
        }
    }
    return false;
}
