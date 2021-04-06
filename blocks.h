#ifndef BLOCKS_H
#define BLOCKS_H

#include "block.h"

#include <QInputDialog>
#include <QMessageBox>

class BeginBlock: public Block {
public:
    void execute();
};

class NumberInputBlock: public Block {
public:
    NumberInputBlock(QWidget *parent): parent(parent) {

        this->subblocks = {
            {"Result", Subblock(this)}
        };

    }
    void execute();
private:
    QWidget *parent;
};

class SumBlock: public Block {
public:
    SumBlock() {

        this->subblocks = {
            {"Argument 1", Subblock(this)},
            {"Argument 2", Subblock(this)},
            {"Result", Subblock(this)}
        };

    }

    void execute();
};

class NumberOutputBlock: public Block {
public:
    NumberOutputBlock(QWidget *parent): parent(parent) {
        this->subblocks = {
            {"Argument 1", Subblock(this)},
        };
    }

    void execute();

private:
    QWidget *parent;
};
#endif // BLOCKS_H
