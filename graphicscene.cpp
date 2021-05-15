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

#define INIT_LINE_PEN()     QPen pen(Qt::black); \
                            QBrush brush; \
                            brush.setColor(Qt::black); \
                            brush.setStyle(Qt::SolidPattern)

GraphicScene::GraphicScene(QObject *parent) : QGraphicsScene(parent)
{

}

GraphicScene::~GraphicScene()
{

}

void GraphicScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!isBlockSelected){
        return;
    }

    INIT_LINE_PEN();

    if (!startArea){
            auto area = isOutputConnectArea(event);
            if (!area){
                addBlock(event);
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

void GraphicScene::drawDefaultBlock(Block *block) {
    INIT_PEN();

    inputConnectionArea.push_back(Area(
                                      block,
                                      nullptr,
                                      QVector4D(block->getPos().x(), block->getPos().y(), block->getPos().x()+BLOCK_WIDTH, block->getPos().y()+BLOCK_HEADER_HEIGHT)));
    addRect(block->getPos().x(), block->getPos().y(), BLOCK_WIDTH, BLOCK_HEADER_HEIGHT, pen, brush);
    path.addText(block->getPos().x() + 20, block->getPos().y() + 20, font,  block->getName());

    int heightOffset = BLOCK_HEADER_HEIGHT;
    auto keys = block->getSubblocksKeys();

    for (int i=0; i<keys.size(); i++) {

        path.addText(block->getPos().x() + 5, block->getPos().y() + heightOffset + 10, font,  keys[i]);
        addRect(block->getPos().x(), block->getPos().y()+heightOffset, 100, SUBBLOCK_HEIGHT, pen, brush);

        Area connectionArea(
                    block,
                    block->getSubblock(keys[i]),
                    QVector4D(block->getPos().x(), block->getPos().y()+heightOffset, block->getPos().x()+BLOCK_WIDTH, block->getPos().y()+heightOffset+SUBBLOCK_HEIGHT));

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

void GraphicScene::drawBlock(Block *block)
{

    switch (block->getType()) {
    case START:
        drawBeginBlock(block);
        program.setBegin(block);
        break;
    default:
        drawDefaultBlock(block);
        break;
    }

}

void GraphicScene::drawLink(Block::Subblock::Link &link)
{
    INIT_LINE_PEN();

    if (link.type != Block::Subblock::LinkType::NO_LINK) {
        QPointF firstPoint = link.points[0];
        addEllipse(firstPoint.x()-5, firstPoint.y()-5, 10, 10, pen, brush);

        QPointF lastPoint = link.points[link.points.size()-1];
        QPolygonF polygon;
        polygon << QPointF(lastPoint.x(), lastPoint.y()+7) << QPointF(lastPoint.x()-7, lastPoint.y()) << QPointF(lastPoint.x(), lastPoint.y()-7) << QPointF(lastPoint.x()+7, lastPoint.y());
        addPolygon(polygon, pen, brush);

        for (int i=0; i<link.points.size()-1; i++) {
            addLine(link.points[i].x(),
                    link.points[i].y(),
                    link.points[i+1].x(),
                    link.points[i+1].y(),
                    QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap));
        }
    }
}

void GraphicScene::drawBeginBlock(Block *block) {
    INIT_PEN();

    addRect(block->getPos().x(), block->getPos().y(), 100, 100, pen, brush);
    outputConnectionArea.push_back(Area(
                                       block,
                                       nullptr,
                                       QVector4D(block->getPos().x(), block->getPos().y(), block->getPos().x()+100, block->getPos().y()+100)));
    path.addText(block->getPos().x() + 30, block->getPos().y() + 50, font,  block->getName());
    this->addPath(path, QPen(QBrush(Qt::black), 0), QBrush(Qt::black));
}

void GraphicScene::addBlock(QGraphicsSceneMouseEvent *event) {

    auto block = BlockFabrica::fromBlockType((QWidget*)this->parent(), buttonType, event->scenePos());
    program.addBlock(block);
    drawBlock(block);
    previousPoint = event->scenePos();
}

void GraphicScene::setProgram(Program p)
{
    clear();
    program = p;

    for (auto b: program.getBlocks()) {
        drawBlock(b);
        drawLink(b->getEndLink());

        for (auto &sb: b->getSubblocks()) {
            drawLink(sb.second.getLink());
        }
    }
}

Program& GraphicScene::getProgram()
{
    return program;
}

void GraphicScene::setButtonType(const BlockType &value)
{
    buttonType = value;
    isBlockSelected = true;
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

void GraphicScene::clearCanvas(){
    clear();
    inputConnectionArea.clear();
    outputConnectionArea.clear();

    program = Program();

    startArea = nullptr;

    linkPoints.clear();
}
