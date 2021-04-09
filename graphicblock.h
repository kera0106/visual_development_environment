#ifndef GRAPHICBLOCK_H
#define GRAPHICBLOCK_H

#include <QPainterPath>
#include <QVector4D>
#include <QVector2D>
#include "graphicscene.h"



class Graphicblock
{
public:    
    Graphicblock();

    static Graphicblock& createBlock(const ButtonType &value, QGraphicsSceneMouseEvent *event);

public:
     QVector4D area;
     std::vector<QVector4D> lines;
     std::vector<std::pair<QVector2D, std::string>> texts;

     void draw(GraphicScene *scene);
};

#endif // GRAPHICBLOCK_H
