#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include "block.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QVector4D>
#include <QVector>

#include "blocktype.h"
#include "blocks.h"

struct Area {
    Block *block = nullptr;
    Block::Subblock *subblock = nullptr;

    QVector4D rect;

    Area() {}

    Area(Block *block, Block::Subblock *subblock, QVector4D rect):
        block(block), subblock(subblock), rect(rect) {}
};

class GraphicScene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit GraphicScene(QObject *parent = 0);
    Area* isInputConnectArea(QGraphicsSceneMouseEvent *event);
    Area* isOutputConnectArea(QGraphicsSceneMouseEvent *event);
    ~GraphicScene();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

public:
    std::vector<Area> inputConnectionArea;
    std::vector<Area> outputConnectionArea;

    QVector<Block*> blocks;
    BeginBlock *begin;

    void setButtonType(const BlockType &value);


    template<typename T>
    void drawBlock(T *block, QGraphicsSceneMouseEvent *);

    void drawBlock(QGraphicsSceneMouseEvent *);

    BeginBlock* getBeginBlock() { return this->begin; }
    QVector<Block*> &getBlocks() { return this->blocks; }
private:
    QPointF previousPoint;
    QVector<QPointF> linkPoints;
    Area* startArea = nullptr;
    BlockType buttonType;
};

#endif // PAINTSCENE_H
