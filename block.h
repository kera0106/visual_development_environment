#ifndef BLOCK_H
#define BLOCK_H

#include <QPointF>
#include <QVariant>
#include <QVector>

#include "blocktype.h"

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
            SUBBLOCK_SUBBLOCK,
            SUBBLOCK_BLOCK,
        };

        struct Link {
            LinkType type;

            Block *blockLink = nullptr;
            Subblock *subblockLink = nullptr;

            Link():
                type(NO_LINK), blockLink(nullptr), subblockLink(nullptr) {}

            Link(Subblock *subblock):
                type(LinkType::SUBBLOCK_SUBBLOCK), blockLink(nullptr), subblockLink(subblock) {}

            Link(Block *block):
                type(LinkType::SUBBLOCK_BLOCK), blockLink(block), subblockLink(nullptr) {}

            QVariant getResult() {
                switch (type) {
                case LinkType::SUBBLOCK_BLOCK:
                    return blockLink->result;
                case LinkType::SUBBLOCK_SUBBLOCK:
                    return subblockLink->block->result;
                case LinkType::NO_LINK:
                    return QVariant();
                }
            }
        };

        Subblock(SubblockType type = SubblockType::INPUT): type(type) {}
        Subblock(Block *block, SubblockType type): block(block), type(type) {}

        void LinkTo(Subblock* subblock) { this->link = Link(subblock); }
        void LinkTo(Block* block) { this->link = Link(block); }

        QVariant getResult() { return link.getResult(); }
        SubblockType getType() { return type; }

        Link getLink() { return link; }

    private:

        Block *block;
        Link link;
        SubblockType type;

    };

    Block(QPointF pos): pos(pos) {}

    virtual void execute()=0;

    void setEnd(Block *block) { this->end = block; }
    QVariant getResult() { return this->result; }

    Subblock* getSubblock(QString name) {
        for (auto &el: subblocks) {
            if (el.first == name) {
                return &el.second;
            }
        }
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

protected:

    BlockType type;
    QPointF pos;

    QVariant result;
    Block* end = nullptr;

    QString name;
    QVector<QPair<QString, Subblock>> subblocks;

};

#endif // BLOCK_H
