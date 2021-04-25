#include "blockfabrica.h"
#include "graphicscene.h"

#define BLOCK_HEADER_HEIGHT 30
#define SUBBLOCK_HEIGHT 20
#define BLOCK_WIDTH 100

#define INIT_PEN()     const QPen &pen = QPen(); \
                       const QBrush &brush = QBrush(); \
                       QPainterPath path; \
                       QFont font; \
                       font.setPixelSize(12); \
                       font.setBold(false); \
                       font.setFamily("Arial")

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

    if (!startArea){
            auto area = isOutputConnectArea(event);
            if (!area){
                drawBlock(event);
                return;
            }

            linkPoints = {event->scenePos()};

            previousPoint = event->scenePos();
            addEllipse(event->scenePos().x()-5, event->scenePos().y()-5, 10, 10, pen, brush);
            startArea = area;
    }

    else{
            addLine(previousPoint.x(),
                        previousPoint.y(),
                        event->scenePos().x(),
                        event->scenePos().y(),
                        QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap));
            linkPoints.push_back(event->scenePos());
            previousPoint = event->scenePos();
            auto area = isInputConnectArea(event);
            if (area){

                if (startArea->subblock && startArea->subblock->getType() == Block::SubblockType::GOTO) {
                    startArea->subblock->LinkTo(area->block, linkPoints);
                } else if (startArea->subblock && area->subblock) {
                    area->subblock->LinkTo(startArea->subblock, linkPoints);
                } else {
                    startArea->block->setEnd(area->block, linkPoints);
                }

                startArea = nullptr;
                QPolygonF polygon;
                polygon << QPoint(event->scenePos().x(), event->scenePos().y()+7) << QPoint(event->scenePos().x()-7, event->scenePos().y()) << QPoint(event->scenePos().x(), event->scenePos().y()-7) << QPoint(event->scenePos().x()+7, event->scenePos().y());
                addPolygon(polygon, pen, brush);

            }
    }
}

void GraphicScene::drawBlock(Block *block, QGraphicsSceneMouseEvent *event) {
    INIT_PEN();

    inputConnectionArea.push_back(Area(
                                      block,
                                      nullptr,
                                      QVector4D(event->scenePos().x(), event->scenePos().y(), event->scenePos().x()+BLOCK_WIDTH, event->scenePos().y()+BLOCK_HEADER_HEIGHT)));
    addRect(event->scenePos().x(), event->scenePos().y(), BLOCK_WIDTH, BLOCK_HEADER_HEIGHT, pen, brush);
    path.addText(event->scenePos().x() + 20, event->scenePos().y() + 20, font,  block->getName());

    int heightOffset = BLOCK_HEADER_HEIGHT;
    auto keys = block->getSubblocksKeys();

    for (int i=0; i<keys.size(); i++) {

        path.addText(event->scenePos().x() + 5, event->scenePos().y() + heightOffset + 10, font,  keys[i]);
        addRect(event->scenePos().x(), event->scenePos().y()+heightOffset, 100, SUBBLOCK_HEIGHT, pen, brush);

        Area connectionArea(
                    block,
                    block->getSubblock(keys[i]),
                    QVector4D(event->scenePos().x(), event->scenePos().y()+heightOffset, event->scenePos().x()+BLOCK_WIDTH, event->scenePos().y()+heightOffset+SUBBLOCK_HEIGHT));

        switch (block->getSubblock(keys[i])->getType()) {
        case Block::SubblockType::INPUT:
            inputConnectionArea.push_back(connectionArea);
            break;

        case Block::SubblockType::OUTPUT:
        case Block::SubblockType::GOTO:
            outputConnectionArea.push_back(connectionArea);
            break;
        }

        heightOffset += SUBBLOCK_HEIGHT;
    }

    addPath(path, QPen(QBrush(Qt::black), 0), QBrush(Qt::black));

}

void GraphicScene::drawBeginBlock(Block *block, QGraphicsSceneMouseEvent *event) {
    INIT_PEN();

    addRect(event->scenePos().x(), event->scenePos().y(), 100, 100, pen, brush);
    outputConnectionArea.push_back(Area(
                                       block,
                                       nullptr,
                                       QVector4D(event->scenePos().x(), event->scenePos().y(), event->scenePos().x()+100, event->scenePos().y()+100)));
    path.addText(event->scenePos().x() + 30, event->scenePos().y() + 50, font,  block->getName());
    this->addPath(path, QPen(QBrush(Qt::black), 0), QBrush(Qt::black));
}

void GraphicScene::drawBlock(QGraphicsSceneMouseEvent *event){

    auto block = BlockFabrica::fromBlockType((QWidget*)this->parent(), buttonType, event->pos());
    program.addBlock(block);

    switch (block->getType()) {
    case START:
        drawBeginBlock(block, event);
        program.setBegin(block);
        break;
    default:
        drawBlock(block, event);
        break;
    }
    previousPoint = event->scenePos();
}

void GraphicScene::setButtonType(const BlockType &value)
{
    buttonType = value;
}

Area* GraphicScene::isInputConnectArea(QGraphicsSceneMouseEvent *event){
    for (auto &area: inputConnectionArea){
        if (area.rect.x() < event->scenePos().x() && area.rect.y() < event->scenePos().y() && area.rect.z() > event->scenePos().x() && area.rect.w() > event->scenePos().y()){
            return &area;
        }
    }
    return nullptr;
}

Area* GraphicScene::isOutputConnectArea(QGraphicsSceneMouseEvent *event){
    for (auto &area: outputConnectionArea){
        if (area.rect.x() < event->scenePos().x() && area.rect.y() < event->scenePos().y() && area.rect.z() > event->scenePos().x() && area.rect.w() > event->scenePos().y()){
            return &area;
        }
    }
    return nullptr;
}
