#include "graphicblock.h"


Graphicblock::Graphicblock()
{

}

Graphicblock& Graphicblock::createBlock(const ButtonType &value, QGraphicsSceneMouseEvent *event){
    Graphicblock *block = new Graphicblock(Graphicblock());

    if (value == START){
        block->area = QVector4D(event->scenePos().x(), event->scenePos().y(), 100, 100);
        block->texts.push_back(std::make_pair(QVector2D(event->scenePos().x() + 30, event->scenePos().y() + 50), "Начало"));
    }

    else if (value == INPUT){
        block->area = QVector4D(event->scenePos().x(), event->scenePos().y(), 100, 100);
        block->lines.push_back(QVector4D(event->scenePos().x(), event->scenePos().y() + 30, event->scenePos().x() + 100, event->scenePos().y()+ 30));
        block->texts.push_back(std::make_pair(QVector2D(event->scenePos().x() + 20, event->scenePos().y() + 20), "Ввод числа"));
        block->texts.push_back(std::make_pair(QVector2D(event->scenePos().x() + 5, event->scenePos().y() + 50), "Поле ввода"));

    }

    else if (value == OUTPUT){
        block->area = QVector4D(event->scenePos().x(), event->scenePos().y(), 100, 100);
        block->lines.push_back(QVector4D(event->scenePos().x(), event->scenePos().y() + 30, event->scenePos().x() + 100, event->scenePos().y()+ 30));
        block->texts.push_back(std::make_pair(QVector2D(event->scenePos().x() + 20, event->scenePos().y() + 20), "Вывод числа"));
        block->texts.push_back(std::make_pair(QVector2D(event->scenePos().x() + 5, event->scenePos().y() + 50), "Поле вывода"));

    }

    else if (value == SUM){
        block->area = QVector4D(event->scenePos().x(), event->scenePos().y(), 100, 100);
        block->lines.push_back(QVector4D(event->scenePos().x(), event->scenePos().y() + 30, event->scenePos().x() + 100, event->scenePos().y()+ 30));
        block->lines.push_back(QVector4D(event->scenePos().x(), event->scenePos().y() + 75, event->scenePos().x() + 100, event->scenePos().y()+ 75));
        block->lines.push_back(QVector4D(event->scenePos().x(), event->scenePos().y() + 55, event->scenePos().x() + 100, event->scenePos().y()+ 55));
        block->texts.push_back(std::make_pair(QVector2D(event->scenePos().x() + 30, event->scenePos().y() + 20), "Сумма"));
        block->texts.push_back(std::make_pair(QVector2D(event->scenePos().x() + 5, event->scenePos().y() + 50), "Слагаемое 1"));
        block->texts.push_back(std::make_pair(QVector2D(event->scenePos().x() + 5, event->scenePos().y() + 70), "Слагаемое 2"));
        block->texts.push_back(std::make_pair(QVector2D(event->scenePos().x() + 5, event->scenePos().y() + 90), "Результат"));
    }


    return *block;
}

void Graphicblock::draw(GraphicScene* scene){
    const QPen &pen = QPen();
    const QBrush &brush = QBrush();
    QPainterPath path;
    QFont font;
    font.setPixelSize(12);
    font.setBold(false);
    font.setFamily("Arial");

    scene->addRect(area.x(), area.y(), area.z(), area.w(), pen, brush);
    for (int i=0; i<lines.size(); i++){
        scene->addLine(lines[i].x(), lines[i].y(), lines[i].z(), lines[i].w(), pen);
    }
    for (int i=0; i<texts.size(); i++){
        int x = texts[i].first.x();
        int y = texts[i].first.y();
        const QString str = QString::fromUtf8(texts[i].second.c_str());
        path.addText(x, y, font, str);
    }
    scene->addPath(path, QPen(QBrush(Qt::black), 0), QBrush(Qt::black));
}
