#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include "block.h"

#include <QPainterPath>
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

    std::vector<Area> inputConnectionArea;
    std::vector<Area> outputConnectionArea;

    explicit GraphicScene(QObject *parent = 0);
    Area* isInputConnectArea(QGraphicsSceneMouseEvent *event);
    Area* isOutputConnectArea(QGraphicsSceneMouseEvent *event);
    ~GraphicScene();

    void setButtonType(const BlockType &value);

    void drawBeginBlock(Block*);
    void drawDefaultBlock(Block*);
    void drawBlock(Block*);
    void drawLink(Block::Subblock::Link&);

    void addBlock(QGraphicsSceneMouseEvent *);

    void clearCanvas();

    void setProgram(Program p);
    Program& getProgram();

    Block* getBeginBlock() { return program.getBeginBlock(); }
    QVector<Block*> &getBlocks() { return program.getBlocks(); }

private:

    Program program;

    Area* startArea = nullptr;
    QPointF previousPoint;

    QVector<QPointF> linkPoints;
    BlockType buttonType;

    bool isBlockSelected = false;

    void mousePressEvent(QGraphicsSceneMouseEvent * event);
};

#endif // PAINTSCENE_H
