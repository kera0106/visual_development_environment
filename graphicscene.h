#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include "block.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QVector4D>

#include "blocks.h"

enum ButtonType {
    START,
    INPUT,
    OUTPUT,
    SUM,
    DIFF,
    MULT,
    DIVIDE
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
    std::vector<Block> blocks;

    void setButtonType(const ButtonType &value);


    template<typename T>
    void drawBlock(T block, QGraphicsSceneMouseEvent *);

    template<typename T>
    void drawBlock(QGraphicsSceneMouseEvent *);

    void drawBlock(QGraphicsSceneMouseEvent *);
private:
    QPointF previousPoint;
    bool isStartPaintLine = false;
    ButtonType buttonType;
};

#endif // PAINTSCENE_H
