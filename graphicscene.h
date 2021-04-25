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
#include "program.h"

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

    Program program;

    void setButtonType(const BlockType &value);

    void drawBeginBlock(Block*, QGraphicsSceneMouseEvent*);
    void drawBlock(Block*, QGraphicsSceneMouseEvent*);

    void drawBlock(QGraphicsSceneMouseEvent *);

    Block* getBeginBlock() { return program.getBeginBlock(); }
    QVector<Block*> &getBlocks() { return program.getBlocks(); }
private:
    QPointF previousPoint;
    QVector<QPointF> linkPoints;
    Area* startArea = nullptr;
    BlockType buttonType;
};

#endif // PAINTSCENE_H
