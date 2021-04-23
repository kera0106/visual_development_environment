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
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };

    }
    void execute();
private:
    QWidget *parent;
};

class StringInputBlock: public Block {
public:
    StringInputBlock(QWidget *parent): parent(parent) {
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
    SumBlock() {
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
    ConcatBlock() {
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
    SubstringBlock() {
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
    DiffBlock() {
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
    MultBlock() {
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
    ModBlock() {
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
    PowBlock() {
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
    SqrtBlock() {
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
    DivBlock() {
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
    NumberOutputBlock(QWidget *parent): parent(parent) {
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
    StringOutputBlock(QWidget *parent): parent(parent) {
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
    LessBlock(){
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
    EqualBlock(){
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
    BiggerBlock(){
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
    EqualsBlock(){
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
    FindBlock(){
        this->name = "Поиск подстроки";
        this->subblocks = {
            {"Строка", Subblock(this, SubblockType::INPUT)},
            {"Подстрока", Subblock(this, SubblockType::INPUT)},
            {"Результат", Subblock(this, SubblockType::OUTPUT)}
        };
    }
    void execute();
};
#endif // BLOCKS_H
