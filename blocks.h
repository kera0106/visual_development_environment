#ifndef BLOCKS_H
#define BLOCKS_H

#include "block.h"

#include <QInputDialog>
#include <QMessageBox>
#include <cmath>

class BeginBlock: public Block {
public:
    BeginBlock(QPointF pos): Block(pos) {
        this->type = BlockType::START;
        this->name = "Начало";
    }
    void execute();
};

class NumberInputBlock: public Block {
public:
    NumberInputBlock(QWidget *parent, QPointF pos): Block(pos), parent(parent) {
        this->type = BlockType::INPUT;
        this->name = "Вввод числа";
        this->subblocks = {
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };

    }
    void execute();
private:
    QWidget *parent;
};

class StringInputBlock: public Block {
public:
    StringInputBlock(QWidget *parent, QPointF pos): Block(pos), parent(parent) {
        this->type = BlockType::INPUT_STR;
        this->name = "Вввод строки";
        this->subblocks = {
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };

    }
    void execute();
private:
    QWidget *parent;
};

class SumBlock: public Block {
public:
    SumBlock(QPointF pos): Block(pos) {
        this->type = BlockType::SUM;
        this->name = "Сумма";
        this->subblocks = {
            {"Слагаемое 1", Subblock(this, SubblockType::INPUT)},
            {"Слагаемое 2", Subblock(this, SubblockType::INPUT)},
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };

    }

    void execute();
};

class ConcatBlock: public Block {
public:
    ConcatBlock(QPointF pos): Block(pos) {
        this->type = BlockType::CONCAT;
        this->name = "Конкатенация";
        this->subblocks = {
            {"Строка 1", Subblock(this, SubblockType::INPUT)},
            {"Строка 2", Subblock(this, SubblockType::INPUT)},
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };

    }

    void execute();
};

class SubstringBlock: public Block {
public:
    SubstringBlock(QPointF pos): Block(pos) {
        this->type = BlockType::SUBSTRING;
        this->name = "Подстрока";
        this->subblocks = {
            {"Строка", Subblock(this, SubblockType::INPUT)},
            {"Начало", Subblock(this, SubblockType::INPUT)},
            {"Конец", Subblock(this, SubblockType::INPUT)},
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };

    }

    void execute();
};

class DiffBlock: public Block {
public:
    DiffBlock(QPointF pos): Block(pos) {
        this->type = BlockType::DIFF;
        this->name = "Разность";
        this->subblocks = {
            {"Уменьшаемое", Subblock(this, SubblockType::INPUT)},
            {"Вычитаемое", Subblock(this, SubblockType::INPUT)},
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };

    }

    void execute();
};

class MultBlock: public Block {
public:
    MultBlock(QPointF pos): Block(pos) {
        this->type = BlockType::MULT;
        this->name = "Умножение";
        this->subblocks = {
            {"Множитель 1", Subblock(this, SubblockType::INPUT)},
            {"Множитель 2", Subblock(this, SubblockType::INPUT)},
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };

    }

    void execute();
};

class ModBlock: public Block {
public:
    ModBlock(QPointF pos): Block(pos) {
        this->type = BlockType::MOD;
        this->name = "Модуль";
        this->subblocks = {
            {"Делимое", Subblock(this, SubblockType::INPUT)},
            {"Делитель", Subblock(this, SubblockType::INPUT)},
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };

    }

    void execute();
};

class PowBlock: public Block {
public:
    PowBlock(QPointF pos): Block(pos) {
        this->type = BlockType::POW;
        this->name = "Степень";
        this->subblocks = {
            {"Основание", Subblock(this, SubblockType::INPUT)},
            {"Показатель", Subblock(this, SubblockType::INPUT)},
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };

    }

    void execute();
};

class SqrtBlock: public Block {
public:
    SqrtBlock(QPointF pos): Block(pos) {
        this->type = BlockType::SQRT;
        this->name = "Корень";
        this->subblocks = {
            {"Аргумент", Subblock(this, SubblockType::INPUT)},
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };

    }

    void execute();
};

class DivBlock: public Block {
public:
    DivBlock(QPointF pos): Block(pos) {
        this->type = BlockType::DIVIDE;
        this->name = "Деление";
        this->subblocks = {
            {"Делимое", Subblock(this, SubblockType::INPUT)},
            {"Делитель", Subblock(this, SubblockType::INPUT)},
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };

    }

    void execute();
};

class NumberOutputBlock: public Block {
public:
    NumberOutputBlock(QWidget *parent, QPointF pos): Block(pos), parent(parent) {
        this->type = BlockType::OUTPUT;
        this->name = "Вывод числа";
        this->subblocks = {
            {"Аргумент", Subblock(this, SubblockType::INPUT)},
        };
    }

    void setEnd(Block *block) { this->end = block; }
    void execute();

private:
    QWidget *parent;
};

class StringOutputBlock: public Block {
public:
    StringOutputBlock(QWidget *parent, QPointF pos): Block(pos), parent(parent) {
        this->type = BlockType::OUTPUT_STR;
        this->name = "Вывод строки";
        this->subblocks = {
            {"Аргумент", Subblock(this, SubblockType::INPUT)},
        };
    }

    void setEnd(Block *block) { this->end = block; }
    void execute();

private:
    QWidget *parent;
};


class LessBlock: public Block{
public:
    LessBlock(QPointF pos): Block(pos) {
        this->type = BlockType::LESS;
        this->name = "Меньше";
        this->subblocks = {
            {"Аргумент1", Subblock(this, SubblockType::INPUT)},
            {"Аргумент2", Subblock(this, SubblockType::INPUT)},
            {"Если", Subblock(this, SubblockType::GOTO)},
            {"Иначе", Subblock(this, SubblockType::GOTO)},
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };
    }
    void execute();
};

class EqualBlock: public Block{
public:
    EqualBlock(QPointF pos): Block(pos) {
        this->type = BlockType::EQUAL;
        this->name = "Равно";
        this->subblocks = {
            {"Аргумент1", Subblock(this, SubblockType::INPUT)},
            {"Аргумент2", Subblock(this, SubblockType::INPUT)},
            {"Если", Subblock(this, SubblockType::GOTO)},
            {"Иначе", Subblock(this, SubblockType::GOTO)},
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };
    }
    void execute();
};

class BiggerBlock: public Block{
public:
    BiggerBlock(QPointF pos): Block(pos) {
        this->type = BlockType::BIGGER;
        this->name = "Больше";
        this->subblocks = {
            {"Аргумент1", Subblock(this, SubblockType::INPUT)},
            {"Аргумент2", Subblock(this, SubblockType::INPUT)},
            {"Если", Subblock(this, SubblockType::GOTO)},
            {"Иначе", Subblock(this, SubblockType::GOTO)},
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };
    }
    void execute();
};

class EqualsBlock: public Block{
public:
    EqualsBlock(QPointF pos): Block(pos) {
        this->type = BlockType::EQUALS;
        this->name = "Сравнение";
        this->subblocks = {
            {"Строка 1", Subblock(this, SubblockType::INPUT)},
            {"Строка 2", Subblock(this, SubblockType::INPUT)},
            {"Равны", Subblock(this, SubblockType::GOTO)},
            {"Не равны", Subblock(this, SubblockType::GOTO)},
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };
    }
    void execute();
};

class FindBlock: public Block{
public:
    FindBlock(QPointF pos): Block(pos) {
        this->type = BlockType::FIND;
        this->name = "Поиск";
        this->subblocks = {
            {"Строка", Subblock(this, SubblockType::INPUT)},
            {"Подстрока", Subblock(this, SubblockType::INPUT)},
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };
    }
    void execute();
};

class ReplaceBlock: public Block{
public:
    ReplaceBlock(QPointF pos): Block(pos) {
        this->type = BlockType::REPLACE;
        this->name = "Сравнение";
        this->subblocks = {
            {"Строка", Subblock(this, SubblockType::INPUT)},
            {"Подстрока", Subblock(this, SubblockType::INPUT)},
            {"Позиция", Subblock(this, SubblockType::INPUT)},
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };
    }
    void execute();
};

class ReverseBlock: public Block{
public:
    ReverseBlock(QPointF pos): Block(pos) {
        this->type = BlockType::REVERSE;
        this->name = "Сравнение";
        this->subblocks = {
            {"Строка", Subblock(this, SubblockType::INPUT)},
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };
    }
    void execute();
};
#endif // BLOCKS_H
