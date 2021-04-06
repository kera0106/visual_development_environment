#include "graphicscene.h"

#include <QVector4D>

GraphicScene::GraphicScene(QObject *parent) : QGraphicsScene(parent)
{
    const QPen &pen = QPen();
    const QBrush &brush = QBrush();
    //addRect(300.0, 100.0, 100.0, 50.0, pen, brush);
    //addRect(300.0, 500.0, 100.0, 50.0, pen, brush);
    //connectionArea.push_back(QVector4D(300, 100, 400, 150));
    //connectionArea.push_back(QVector4D(300, 500, 400, 550));
}

GraphicScene::~GraphicScene()
{

}

void GraphicScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    if (!isStartPaintLine){
//            if (!isConnectArea(event))
//                return;
//            previousPoint = event->scenePos();
//            isStartPaintLine = true;
//    }

//    else{
//            addLine(previousPoint.x(),
//                        previousPoint.y(),
//                        event->scenePos().x(),
//                        event->scenePos().y(),
//                        QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap));
//            previousPoint = event->scenePos();

//            if (isConnectArea(event))
//                isStartPaintLine = false;
//    }

    const QPen &pen = QPen();
    const QBrush &brush = QBrush();
    QPainterPath path;
    QFont font;
    font.setPixelSize(12);
    font.setBold(false);
    font.setFamily("Arial");

    if(buttonType == START){
        addRect(event->scenePos().x(), event->scenePos().y(), 100, 100, pen, brush);
        path.addText(event->scenePos().x() + 30, event->scenePos().y() + 50, font,  "Начало");
        this->addPath(path, QPen(QBrush(Qt::black), 0), QBrush(Qt::black));
    }else if(buttonType == INPUT){
        addRect(event->scenePos().x(), event->scenePos().y(), 100, 100, pen, brush);
        addLine(event->scenePos().x(), event->scenePos().y() + 30, event->scenePos().x() + 100, event->scenePos().y()+ 30, pen);
        path.addText(event->scenePos().x() + 20, event->scenePos().y() + 20, font,  "Ввод числа");
        path.addText(event->scenePos().x() + 5, event->scenePos().y() + 50, font,  "Result");
        this->addPath(path, QPen(QBrush(Qt::black), 0), QBrush(Qt::black));
    }else if(buttonType == OUTPUT){
        addRect(event->scenePos().x(), event->scenePos().y(), 100, 100, pen, brush);
        addLine(event->scenePos().x(), event->scenePos().y() + 30, event->scenePos().x() + 100, event->scenePos().y()+ 30, pen);
        path.addText(event->scenePos().x() + 20, event->scenePos().y() + 20, font,  "Вывод числа");
        path.addText(event->scenePos().x() + 5, event->scenePos().y() + 50, font,  "Argument1");
        this->addPath(path, QPen(QBrush(Qt::black), 0), QBrush(Qt::black));
    }else if(buttonType == SUM){
        addRect(event->scenePos().x(), event->scenePos().y(), 100, 100, pen, brush);
        addLine(event->scenePos().x(), event->scenePos().y() + 30, event->scenePos().x() + 100, event->scenePos().y()+ 30, pen);
        path.addText(event->scenePos().x() + 30, event->scenePos().y() + 20, font,  "Сумма");
        path.addText(event->scenePos().x() + 5, event->scenePos().y() + 50, font,  "Argument1");
        addLine(event->scenePos().x(), event->scenePos().y() + 55, event->scenePos().x() + 100, event->scenePos().y()+ 55, pen);
        path.addText(event->scenePos().x() + 5, event->scenePos().y() + 70, font,  "Argument2");
        addLine(event->scenePos().x(), event->scenePos().y() + 75, event->scenePos().x() + 100, event->scenePos().y()+ 75, pen);
        path.addText(event->scenePos().x() + 5, event->scenePos().y() + 90, font,  "Result");
        this->addPath(path, QPen(QBrush(Qt::black), 0), QBrush(Qt::black));
    }
    previousPoint = event->scenePos();
}

void GraphicScene::setButtonType(const ButtonType &value)
{
    buttonType = value;
}

bool GraphicScene::isConnectArea(QGraphicsSceneMouseEvent *event){
    for (int i=0; i<connectionArea.size(); i++){
        if (connectionArea[i].x() < event->scenePos().x() && connectionArea[i].y() < event->scenePos().y() && connectionArea[i].z() > event->scenePos().x() && connectionArea[i].w() > event->scenePos().y()){
            return true;
        }
    }
    return false;
}
