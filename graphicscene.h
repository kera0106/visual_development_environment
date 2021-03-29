#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>

class GraphicScene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit GraphicScene(QObject *parent = 0);
    bool isConnectArea(QGraphicsSceneMouseEvent *event);
    ~GraphicScene();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

public:
    std::vector<QVector4D> connectionArea;

private:
    QPointF previousPoint;
    bool isStartPaintLine = false;

};

#endif // PAINTSCENE_H
