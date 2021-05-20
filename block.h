#ifndef BLOCK_H
#define BLOCK_H

#include <QJsonArray>
#include <QJsonObject>
#include <QPointF>
#include <QVariant>
#include <QVector>

#include <QDebug>

#include "blocktype.h"
#include "programenvironment.h"

class BlockFabrica;

class Block
{

public:

    enum SubblockType {
        INPUT,
        OUTPUT,
        GOTO
    };

    class Subblock
    {
    public:

        enum LinkType {
            NO_LINK,
            SUBBLOCK,
            BLOCK
        };

        struct Link {
            LinkType type;

            Block *blockLink = nullptr;
            Subblock *subblockLink = nullptr;

            QVector<QPointF> points;

            Link():
                type(NO_LINK), blockLink(nullptr), subblockLink(nullptr) {}

            Link(Subblock *subblock, QVector<QPointF> points):
                type(LinkType::SUBBLOCK), blockLink(nullptr), subblockLink(subblock), points(points) {}

            Link(Block *block, QVector<QPointF> points):
                type(LinkType::BLOCK), blockLink(block), subblockLink(nullptr), points(points) {}

            QVariant getResult() {
                switch (type) {
                case LinkType::BLOCK:
                    return blockLink->result;
                case LinkType::SUBBLOCK:
                    return subblockLink->block->result;
                case LinkType::NO_LINK:
                    return QVariant();
                }
            }

            Block *getBlock() { return blockLink; }

            QJsonObject toJSON() {
                QJsonObject obj;

                obj["link_type"] = this->type;

                QJsonArray jsonPoints;
                for (int i=0; i<points.size(); i++) {
                    QJsonObject jsonPoint;
                    jsonPoint["index"] = i;
                    jsonPoint["point_x"] = points[i].x();
                    jsonPoint["point_y"] = points[i].y();
                    jsonPoints.append(jsonPoint);
                }

                obj["points"] = jsonPoints;

                switch (type) {

                case LinkType::BLOCK:
                    obj["block"] = blockLink->id;
                    break;

                case LinkType::SUBBLOCK:
                    obj["block"] = subblockLink->block->id;
                    obj["subblock"] = subblockLink->index;
                    break;

                }
                return obj;
            }
        };

        Subblock(SubblockType type = SubblockType::INPUT, int index = 0): type(type), index(index) {}
        Subblock(Block *block, SubblockType type, int index): block(block), type(type), index(index) {}

        void LinkTo(Subblock* subblock, QVector<QPointF> points) { this->link = Link(subblock, points); }
        void LinkTo(Block* block, QVector<QPointF> points) { this->link = Link(block, points); }

        QVariant getResult() { return link.getResult(); }
        SubblockType getType() { return type; }

        Link &getLink() { return link; }

        QJsonObject toJSON() {
            QJsonObject obj;

            obj["index"] = index;
            obj["link"] = link.toJSON();

            return obj;
        }

    private:

        int index;
        Block *block;
        Link link;
        SubblockType type;

    };

    Block(QPointF pos): id(current_id++), pos(pos) {}


    virtual void execute(ProgramEnvironment*)=0;
    virtual Block *getNext() { return this->end.getBlock(); }

    void setEnd(Block *block, QVector<QPointF> points) { this->end = Subblock::Link(block, points); }
    Subblock::Link &getEndLink() { return this->end; }

    QVariant getResult() { return this->result; }

    Subblock* getSubblock(QString name) {
        for (auto &el: subblocks) {
            if (el.first == name) {
                return &el.second;
            }
        }
        return nullptr;
    }

    QVector<QPair<QString, Subblock>> &getSubblocks() {
        return subblocks;
    }

    Subblock* getSubblock(int index) {
        return &subblocks[index].second;
    }

    QVector<QString> getSubblocksKeys() {
        QVector<QString> keys;
        for (auto &el: subblocks) {
            keys.push_back(el.first);
        }
        return keys;
    }

    QString getName() { return name; }

    BlockType getType() { return type; }

    QJsonObject toJSON() {
        QJsonObject obj;

        obj["id"] = this->id;
        obj["type"] = this->type;
        obj["pos_x"] = this->pos.x();
        obj["pos_y"] = this->pos.y();
        obj["end"] = this->end.toJSON();

        QJsonArray jsonSubblocks;
        for (auto &subblock: subblocks) {
            jsonSubblocks.append(subblock.second.toJSON());
        }
        obj["subblocks"] = jsonSubblocks;

        return obj;
    }

    int getId() {
        return id;
    }

    QPointF getPos() {
        return this->pos;
    }

protected:

    int id;

    BlockType type;
    QPointF pos;

    QVariant result;
    Subblock::Link end;

    QString name;
    QVector<QPair<QString, Subblock>> subblocks;

private:

    friend BlockFabrica;
    static int current_id;

};

#endif // BLOCK_H
