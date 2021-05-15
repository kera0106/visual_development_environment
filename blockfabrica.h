#ifndef BLOCKFABRICA_H
#define BLOCKFABRICA_H

#include <QMap>

#include "block.h"
#include "blocks.h"
#include "blocktype.h"

class BlockFabrica {
public:

    static Block* fromBlockType(QWidget *parent, BlockType type, QPointF pos) {
        switch (type) {

        case START:
            return new BeginBlock(pos);
        case INPUT:
            return new NumberInputBlock(parent, pos);
        case OUTPUT:
            return new NumberOutputBlock(parent, pos);
        case SUM:
            return new SumBlock(pos);
        case DIFF:
            return new DiffBlock(pos);
        case MULT:
            return new MultBlock(pos);
        case DIVIDE:
            return new DivBlock(pos);
        case MOD:
            return new ModBlock(pos);
        case POW:
            return new PowBlock(pos);
        case SQRT:
            return new SqrtBlock(pos);
        case LESS:
            return new LessBlock(pos);
        case BIGGER:
            return new BiggerBlock(pos);
        case EQUAL:
            return new EqualBlock(pos);
        case INPUT_STR:
            return new StringInputBlock(parent, pos);
        case OUTPUT_STR:
            return new StringOutputBlock(parent, pos);
        case CONCAT:
            return new ConcatBlock(pos);
        case SUBSTRING:
            return new SubstringBlock(pos);
        case EQUALS:
            return new EqualsBlock(pos);
        case FIND:
            return new FindBlock(pos);
        case REPLACE:
            return new ReplaceBlock(pos);
        case REVERSE:
            return new ReverseBlock(pos);
        case NEGATION:
            return new NegationBlock(pos);
        case CONJUNCTION:
            return new ConjunctionBlock(pos);
        case DISJUNCTION:
            return new DisjunctionBlock(pos);
        }
    }
    static Block* fromJSON(QWidget *parent, QJsonObject jsonBlock) {

        BlockType type = (BlockType)jsonBlock["type"].toInt();
        QPointF pos(jsonBlock["pos_x"].toDouble(), jsonBlock["pos_y"].toDouble());

        Block *block = BlockFabrica::fromBlockType(parent, type, pos);
        block->id = jsonBlock["id"].toInt();

        return block;
    }

};

#endif // BLOCKFABRICA_H
