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
    if (!isStartPaintLine){
            if (!isOutputConnectArea(event)){
                drawBlock(event);
                return;
            }
            previousPoint = event->scenePos();
            addEllipse(event->scenePos().x()-5, event->scenePos().y()-5, 10, 10, pen, brush);
            isStartPaintLine = true;
    }

    else{
            addLine(previousPoint.x(),
                        previousPoint.y(),
                        event->scenePos().x(),
                        event->scenePos().y(),
                        QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap));
            previousPoint = event->scenePos();
            if (isInputConnectArea(event)){
                isStartPaintLine = false;
                QPolygonF polygon;
                polygon << QPoint(event->scenePos().x(), event->scenePos().y()+7) << QPoint(event->scenePos().x()-7, event->scenePos().y()) << QPoint(event->scenePos().x(), event->scenePos().y()-7) << QPoint(event->scenePos().x()+7, event->scenePos().y());
                addPolygon(polygon, pen, brush);
            }
    }



}

template<typename T>
void GraphicScene::drawBlock(T block, QGraphicsSceneMouseEvent *event) {
    INIT_PEN();

    inputConnectionArea.push_back(QVector4D(event->scenePos().x(), event->scenePos().y(), event->scenePos().x()+BLOCK_WIDTH, event->scenePos().y()+BLOCK_HEADER_HEIGHT));
    addRect(event->scenePos().x(), event->scenePos().y(), BLOCK_WIDTH, BLOCK_HEADER_HEIGHT, pen, brush);
    path.addText(event->scenePos().x() + 20, event->scenePos().y() + 20, font,  block.getName());

    int heightOffset = BLOCK_HEADER_HEIGHT;
    auto keys = block.getSubblocksKeys();

    for (int i=0; i<keys.size(); i++) {

        path.addText(event->scenePos().x() + 5, event->scenePos().y() + heightOffset + 10, font,  keys[i]);
        addRect(event->scenePos().x(), event->scenePos().y()+heightOffset, 100, SUBBLOCK_HEIGHT, pen, brush);

        QVector4D connectionArea(event->scenePos().x(), event->scenePos().y()+heightOffset, event->scenePos().x()+BLOCK_WIDTH, event->scenePos().y()+heightOffset+SUBBLOCK_HEIGHT);
        switch (block.getSubblock(keys[i])->getType()) {
        case Block::SubblockType::INPUT:
            inputConnectionArea.push_back(connectionArea);

        case Block::SubblockType::OUTPUT:
            outputConnectionArea.push_back(connectionArea);
        }

        heightOffset += SUBBLOCK_HEIGHT;
    }

    addPath(path, QPen(QBrush(Qt::black), 0), QBrush(Qt::black));

}

template<>
void GraphicScene::drawBlock(BeginBlock block, QGraphicsSceneMouseEvent *event) {
    INIT_PEN();

    addRect(event->scenePos().x(), event->scenePos().y(), 100, 100, pen, brush);
    outputConnectionArea.push_back(QVector4D(event->scenePos().x(), event->scenePos().y(), event->scenePos().x()+100, event->scenePos().y()+100));
    path.addText(event->scenePos().x() + 30, event->scenePos().y() + 50, font,  block.getName());
    this->addPath(path, QPen(QBrush(Qt::black), 0), QBrush(Qt::black));

}

template<typename T>
void GraphicScene::drawBlock(QGraphicsSceneMouseEvent *event) {

    T block;
    drawBlock(block, event);

}

void GraphicScene::drawBlock(QGraphicsSceneMouseEvent *event){

    if(buttonType == START){
        drawBlock<BeginBlock>(event);
    }else if(buttonType == INPUT){

        QGraphicsView * const localFirst = this->views().first();
        NumberInputBlock block((QWidget*)this->parent());
        drawBlock(block, event);

    }else if(buttonType == OUTPUT){

        QGraphicsView * const localFirst = this->views().first();
        NumberOutputBlock block((QWidget*)this->parent());
        drawBlock(block, event);

    } else if(buttonType == SUM){

        drawBlock<SumBlock>(event);

    } else if(buttonType == DIFF){

        drawBlock<DiffBlock>(event);

    } else if(buttonType == MULT){

        drawBlock<MultBlock>(event);

    } else if(buttonType == DIVIDE){

        drawBlock<DivBlock>(event);

    }


    previousPoint = event->scenePos();
}

void GraphicScene::setButtonType(const ButtonType &value)
{
    buttonType = value;
}

bool GraphicScene::isInputConnectArea(QGraphicsSceneMouseEvent *event){
    for (int i=0; i<inputConnectionArea.size(); i++){
        if (inputConnectionArea[i].x() < event->scenePos().x() && inputConnectionArea[i].y() < event->scenePos().y() && inputConnectionArea[i].z() > event->scenePos().x() && inputConnectionArea[i].w() > event->scenePos().y()){
            return true;
        }
    }
    return false;
}

bool GraphicScene::isOutputConnectArea(QGraphicsSceneMouseEvent *event){
    for (int i=0; i<outputConnectionArea.size(); i++){
        if (outputConnectionArea[i].x() < event->scenePos().x() && outputConnectionArea[i].y() < event->scenePos().y() && outputConnectionArea[i].z() > event->scenePos().x() && outputConnectionArea[i].w() > event->scenePos().y()){
            return true;
        }
    }
    return false;
}
