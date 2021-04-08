#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QVector4D>


enum ButtonType {
    START,
    INPUT,
    OUTPUT,
    SUM,
    DIFFERENCE,
    MULT,
    DIVISION
};
class GraphicScene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit GraphicScene(QObject *parent = 0);
    bool isInputConnectArea(QGraphicsSceneMouseEvent *event);
    bool isOutputConnectArea(QGraphicsSceneMouseEvent *event);
    ~GraphicScene();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

public:
    std::vector<QVector4D> inputConnectionArea;
    std::vector<QVector4D> outputConnectionArea;

    void setButtonType(const ButtonType &value);

    void drawBlock(QGraphicsSceneMouseEvent *);
private:
    QPointF previousPoint;
    bool isStartPaintLine = false;
    ButtonType buttonType;
};

#endif // PAINTSCENE_H
