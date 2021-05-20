#ifndef PROGRAM_H
#define PROGRAM_H

#include "block.h"
#include "blockfabrica.h"
#include "blocks.h"

#include <programenvironment.h>

class Program
{
public:
    Program() {}
    Program(BeginBlock *beginBlock): beginBlock(beginBlock) {}

    Program(QWidget *parent, QJsonObject jsonProgram) {

        QJsonArray jsonBlocks = jsonProgram["blocks"].toArray();
        for (auto jsonBlock: jsonBlocks) {
            Block *block = BlockFabrica::fromJSON(parent, jsonBlock.toObject());
            addBlock(block);
            if (block->getId() == jsonProgram["id"].toInt()) {
                setBegin(block);
            }
        }

        for (int i=0; i<jsonBlocks.size(); i++) {
            auto blockObj = jsonBlocks[i].toObject();

            auto blockEnd = blockObj["end"].toObject();
            auto endBlockId = blockEnd["block"].toInt();
            auto endLinkType = (Block::Subblock::LinkType)blockEnd["link_type"].toInt();
            auto endBlock = getBlockWithId(endBlockId);

            if (endLinkType == Block::Subblock::LinkType::BLOCK) {
                blocks[i]->setEnd(endBlock, pointsFromJSON(blockEnd["points"].toArray()));
            }

            auto subblocks = blockObj["subblocks"].toArray();
            for (int j=0; j<subblocks.size(); j++) {
                auto subblockObj = subblocks[j].toObject();
                auto index = subblockObj["index"].toInt();

                auto linkObj = subblockObj["link"].toObject();
                auto linkType = (Block::Subblock::LinkType)linkObj["link_type"].toInt();
                auto linkPoints = pointsFromJSON(linkObj["points"].toArray());

                switch (linkType) {

                case Block::Subblock::LinkType::SUBBLOCK: {
                    int blockId = linkObj["block"].toInt();
                    int subblockIndex = linkObj["subblock"].toInt();

                    blocks[i]->getSubblock(index)->LinkTo(getBlockWithId(blockId)->getSubblock(subblockIndex), linkPoints);
                    break;
                }

                case Block::Subblock::LinkType::BLOCK: {
                    int blockId = linkObj["block"].toInt();

                    blocks[i]->getSubblock(index)->LinkTo(getBlockWithId(blockId), linkPoints);
                    break;
                }

                }
            }
        }
    }

    void execute() {

        Block *next = beginBlock;
        if (!next){
            return;
        }

        while (next) {
            next->execute(env);
            next = next->getNext();
        }

    }

    void setBegin(Block *beginBlock) { this->beginBlock = beginBlock; }
    void addBlock(Block *block) { this->blocks.push_back(block); }

    Block *getBeginBlock() { return this->beginBlock; }
    QVector<Block*> &getBlocks() { return this->blocks; }

    QJsonObject toJSON() {
        QJsonObject obj;

        obj["begin_id"] = beginBlock->getId();

        QJsonArray jsonBlocks;
        for (auto block: blocks) {
            jsonBlocks.append(block->toJSON());
        }
        obj["blocks"] = jsonBlocks;

        return obj;
    }

    Block *getBlockWithId(int id) {

        for (auto block: blocks) {
            if (block->getId() == id) {
                return block;
            }
        }

        return nullptr;
    }

    QVector<QPointF> pointsFromJSON(QJsonArray jsonPoints) {
        QVector<QPointF> points;

        for (auto jsonPoint: jsonPoints) {
            auto pointObj = jsonPoint.toObject();
            points.push_back(QPointF(pointObj["point_x"].toDouble(), pointObj["point_y"].toDouble()));
        }

        return points;
    }

    void setEnvironment(ProgramEnvironment *env) {
        this->env = env;
    }

private:
    ProgramEnvironment *env = nullptr;
    QVector<Block*> blocks;
    Block *beginBlock = nullptr;
};

#endif // PROGRAM_H
