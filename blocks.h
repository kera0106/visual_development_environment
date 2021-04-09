#ifndef BLOCKS_H
#define BLOCKS_H

#include "block.h"

#include <QInputDialog>
#include <QMessageBox>
#include <cmath>

class BeginBlock: public Block {
public:
    BeginBlock() {
        this->name = "Начало";
    }
    void execute();
};

class NumberInputBlock: public Block {
public:
    NumberInputBlock(QWidget *parent): parent(parent) {
        this->name = "Вввод числа";
        this->subblocks = {
            {"Result", Subblock(this, SubblockType::OUTPUT)}
        };

    }
    void execute();
private:
    QWidget *parent;
};

class SumBlock: public Block {
public:
    SumBlock() {
        this->name = "Сумма";
        this->subblocks = {
            {"Argument 1", Subblock(this, SubblockType::INPUT)},
            {"Argument 2", Subblock(this, SubblockType::INPUT)},
            {"Result", Subblock(this, SubblockType::OUTPUT)}
        };

    }

    void execute();
};

class DiffBlock: public Block {
public:
    DiffBlock() {
        this->name = "Разность";
        this->subblocks = {
            {"Argument 1", Subblock(this, SubblockType::INPUT)},
            {"Argument 2", Subblock(this, SubblockType::INPUT)},
            {"Result", Subblock(this, SubblockType::OUTPUT)}
        };

    }

    void execute();
};

class MultBlock: public Block {
public:
    MultBlock() {
        this->name = "Умножение";
        this->subblocks = {
            {"Argument 1", Subblock(this, SubblockType::INPUT)},
            {"Argument 2", Subblock(this, SubblockType::INPUT)},
            {"Result", Subblock(this, SubblockType::OUTPUT)}
        };

    }

    void execute();
};

class ModBlock: public Block {
public:
    ModBlock() {
        this->name = "Модуль";
        this->subblocks = {
            {"Argument 1", Subblock(this, SubblockType::INPUT)},
            {"Argument 2", Subblock(this, SubblockType::INPUT)},
            {"Result", Subblock(this, SubblockType::OUTPUT)}
        };

    }

    void execute();
};

class PowBlock: public Block {
public:
    PowBlock() {
        this->name = "Степень";
        this->subblocks = {
            {"Argument 1", Subblock(this, SubblockType::INPUT)},
            {"Argument 2", Subblock(this, SubblockType::INPUT)},
            {"Result", Subblock(this, SubblockType::OUTPUT)}
        };

    }

    void execute();
};

class SqrtBlock: public Block {
public:
    SqrtBlock() {
        this->name = "Корень";
        this->subblocks = {
            {"Argument", Subblock(this, SubblockType::INPUT)},
            {"Result", Subblock(this, SubblockType::OUTPUT)}
        };

    }

    void execute();
};

class DivBlock: public Block {
public:
    DivBlock() {
        this->name = "Деление";
        this->subblocks = {
            {"Argument 1", Subblock(this, SubblockType::INPUT)},
            {"Argument 2", Subblock(this, SubblockType::INPUT)},
            {"Result", Subblock(this, SubblockType::OUTPUT)}
        };

    }

    void execute();
};

class NumberOutputBlock: public Block {
public:
    NumberOutputBlock(QWidget *parent): parent(parent) {
        this->name = "Вывод числа";
        this->subblocks = {
            {"Argument 1", Subblock(this, SubblockType::INPUT)},
        };
    }

    void execute();

private:
    QWidget *parent;
};
#endif // BLOCKS_H
