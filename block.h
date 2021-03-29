#ifndef BLOCK_H
#define BLOCK_H

#include <QMap>
#include <QPointF>
#include <QVariant>

class Block
{

protected:

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

            Block *blockLink;
            Subblock *subblockLink;

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

        Subblock() {}
        Subblock(Block *block): block(block) {}

        void LinkTo(Subblock* subblock) { this->link = Link(subblock); }
        void LinkTo(Block* block) { this->link = Link(block); }

        QVariant getResult() { return link.getResult(); }

    private:

        Block *block;
        Link link;

    };

public:

    virtual void execute()=0;

    void setEnd(Block *block) { this->end = block; }
    QVariant getResult() { return this->result; }
    Subblock* getSubblock(QString name) { return &subblocks[name]; }

protected:

    QPointF pos;

    QVariant result;
    Block* end;

    QMap<QString, Subblock> subblocks;

};

#endif // BLOCK_H
