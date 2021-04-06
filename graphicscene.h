#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>


enum ButtonType {
    START,
    INPUT,
    OUTPUT,
    SUM
};
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

    void setButtonType(const ButtonType &value);

private:
    QPointF previousPoint;
    bool isStartPaintLine = false;
    ButtonType buttonType;
};

#endif // PAINTSCENE_H
