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
            previousPoint = event->scenePos();
            auto area = isInputConnectArea(event);
            if (area){

                if (startArea->subblock && startArea->subblock->getType() == Block::SubblockType::GOTO) {
                    startArea->subblock->LinkTo(area->block);
                } else if (startArea->subblock && area->subblock){
                    area->subblock->LinkTo(startArea->subblock);
                } else {
                    startArea->block->setEnd(area->block);
                }

                startArea = nullptr;
                QPolygonF polygon;
                polygon << QPoint(event->scenePos().x(), event->scenePos().y()+7) << QPoint(event->scenePos().x()-7, event->scenePos().y()) << QPoint(event->scenePos().x(), event->scenePos().y()-7) << QPoint(event->scenePos().x()+7, event->scenePos().y());
                addPolygon(polygon, pen, brush);

            }
    }
}

template<typename T>
void GraphicScene::drawBlock(T *block, QGraphicsSceneMouseEvent *event) {
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
        case Block::SubblockType::GOTO:
            inputConnectionArea.push_back(connectionArea);
            break;

        case Block::SubblockType::OUTPUT:
            outputConnectionArea.push_back(connectionArea);
            break;
        }

        heightOffset += SUBBLOCK_HEIGHT;
    }

    addPath(path, QPen(QBrush(Qt::black), 0), QBrush(Qt::black));

}

template<>
void GraphicScene::drawBlock(BeginBlock *block, QGraphicsSceneMouseEvent *event) {
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

    if(buttonType == START){
        auto block = new BeginBlock();
        blocks.push_back(block);
        drawBlock(block, event);

        begin = block;
    }else if(buttonType == INPUT){

        QGraphicsView * const localFirst = this->views().first();
        auto block = new NumberInputBlock((QWidget*)this->parent());
        blocks.push_back(block);
        drawBlock(block, event);

    }else if(buttonType == OUTPUT){

        QGraphicsView * const localFirst = this->views().first();
        auto block = new NumberOutputBlock((QWidget*)this->parent());
        blocks.push_back(block);
        drawBlock(block, event);

    } else if(buttonType == SUM){

        auto block = new SumBlock();
        blocks.push_back(block);
        drawBlock(block, event);

    } else if(buttonType == DIFF){

        auto block = new DiffBlock();
        blocks.push_back(block);
        drawBlock(block, event);

    } else if(buttonType == MULT){

        auto block = new MultBlock();
        blocks.push_back(block);
        drawBlock(block, event);

    } else if(buttonType == DIVIDE){

        auto block = new DivBlock();
        blocks.push_back(block);
        drawBlock(block, event);

    } else if(buttonType == MOD){

        auto block = new ModBlock();
        blocks.push_back(block);
        drawBlock(block, event);

    } else if(buttonType == POW){

        auto block = new PowBlock();
        blocks.push_back(block);
        drawBlock(block, event);

    } else if(buttonType == SQRT){

        auto block = new SqrtBlock();
        blocks.push_back(block);
        drawBlock(block, event);
    }

    previousPoint = event->scenePos();
}

void GraphicScene::setButtonType(const ButtonType &value)
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
