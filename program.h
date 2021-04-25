#ifndef PROGRAM_H
#define PROGRAM_H

#include "block.h"
#include "blocks.h"

class Program
{
public:
    Program() {}
    Program(BeginBlock *beginBlock): beginBlock(beginBlock) {}

    void execute() { beginBlock->execute(); }
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

private:
    QVector<Block*> blocks;
    Block *beginBlock;
};

#endif // PROGRAM_H
