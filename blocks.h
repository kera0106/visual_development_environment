#ifndef BLOCKS_H
#define BLOCKS_H

#include "block.h"

#include <QInputDialog>
#include <QMap>
#include <QMessageBox>
#include <cmath>

class BeginBlock: public Block {
public:
    BeginBlock(QPointF pos): Block(pos) {
        this->type = BlockType::START;
        this->name = "Начало";
    }
    void execute(ProgramEnvironment*);
};

class NumberInputBlock: public Block {
public:
    NumberInputBlock(QPointF pos): Block(pos){
        this->type = BlockType::INPUT;
        this->name = "Ввод числа";
        this->subblocks = {
            {"Результат", Subblock(this, SubblockType::OUTPUT, 0)}
        };

    }
    void execute(ProgramEnvironment*);
    Block* getNext();
private:
    bool isOk;
};

class StringInputBlock: public Block {
public:
    StringInputBlock(QPointF pos): Block(pos) {
        this->type = BlockType::INPUT_STR;
        this->name = "Ввод строки";
        this->subblocks = {
            {"Результат", Subblock(this, SubblockType::OUTPUT, 0)}
        };

    }
    void execute(ProgramEnvironment*);
    Block* getNext();
private:
    bool isOk;
};

class SumBlock: public Block {
public:
    SumBlock(QPointF pos): Block(pos) {
        this->type = BlockType::SUM;
        this->name = "Сумма";
        this->subblocks = {
            {"Слагаемое 1", Subblock(this, SubblockType::INPUT, 0)},
            {"Слагаемое 2", Subblock(this, SubblockType::INPUT, 1)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 2)}
        };

    }

    void execute(ProgramEnvironment*);
};

class ConcatBlock: public Block {
public:
    ConcatBlock(QPointF pos): Block(pos) {
        this->type = BlockType::CONCAT;
        this->name = "Конкатенация";
        this->subblocks = {
            {"Строка 1", Subblock(this, SubblockType::INPUT, 0)},
            {"Строка 2", Subblock(this, SubblockType::INPUT, 1)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 2)}
        };

    }

    void execute(ProgramEnvironment*);
};

class SubstringBlock: public Block {
public:
    SubstringBlock(QPointF pos): Block(pos) {
        this->type = BlockType::SUBSTRING;
        this->name = "Подстрока";
        this->subblocks = {
            {"Строка", Subblock(this, SubblockType::INPUT, 0)},
            {"Начало", Subblock(this, SubblockType::INPUT, 1)},
            {"Конец", Subblock(this, SubblockType::INPUT, 2)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 3)}
        };

    }

    void execute(ProgramEnvironment*);
};

class DiffBlock: public Block {
public:
    DiffBlock(QPointF pos): Block(pos) {
        this->type = BlockType::DIFF;
        this->name = "Разность";
        this->subblocks = {
            {"Уменьшаемое", Subblock(this, SubblockType::INPUT, 0)},
            {"Вычитаемое", Subblock(this, SubblockType::INPUT, 1)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 2)}
        };

    }

    void execute(ProgramEnvironment*);
};

class MultBlock: public Block {
public:
    MultBlock(QPointF pos): Block(pos) {
        this->type = BlockType::MULT;
        this->name = "Умножение";
        this->subblocks = {
            {"Множитель 1", Subblock(this, SubblockType::INPUT, 0)},
            {"Множитель 2", Subblock(this, SubblockType::INPUT, 1)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 2)}
        };

    }

    void execute(ProgramEnvironment*);
};

class ModBlock: public Block {
public:
    ModBlock(QPointF pos): Block(pos) {
        this->type = BlockType::MOD;
        this->name = "Модуль";
        this->subblocks = {
            {"Делимое", Subblock(this, SubblockType::INPUT, 0)},
            {"Делитель", Subblock(this, SubblockType::INPUT, 1)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 2)}
        };

    }

    void execute(ProgramEnvironment*);
};

class PowBlock: public Block {
public:
    PowBlock(QPointF pos): Block(pos) {
        this->type = BlockType::POW;
        this->name = "Степень";
        this->subblocks = {
            {"Основание", Subblock(this, SubblockType::INPUT, 0)},
            {"Показатель", Subblock(this, SubblockType::INPUT, 1)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 2)}
        };

    }

    void execute(ProgramEnvironment*);
};

class SqrtBlock: public Block {
public:
    SqrtBlock(QPointF pos): Block(pos) {
        this->type = BlockType::SQRT;
        this->name = "Корень";
        this->subblocks = {
            {"Аргумент", Subblock(this, SubblockType::INPUT, 0)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 1)}
        };

    }

    void execute(ProgramEnvironment*);
};

class DivBlock: public Block {
public:
    DivBlock(QPointF pos): Block(pos) {
        this->type = BlockType::DIVIDE;
        this->name = "Деление";
        this->subblocks = {
            {"Делимое", Subblock(this, SubblockType::INPUT, 0)},
            {"Делитель", Subblock(this, SubblockType::INPUT, 1)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 2)}
        };

    }

    void execute(ProgramEnvironment*);
};

class NumberOutputBlock: public Block {
public:
    NumberOutputBlock(QPointF pos): Block(pos) {
        this->type = BlockType::OUTPUT;
        this->name = "Вывод числа";
        this->subblocks = {
            {"Аргумент", Subblock(this, SubblockType::INPUT, 0)},
        };
    }

    void execute(ProgramEnvironment*);
    Block* getNext();
private:
    bool isOk;
};

class StringOutputBlock: public Block {
public:
    StringOutputBlock(QPointF pos): Block(pos) {
        this->type = BlockType::OUTPUT_STR;
        this->name = "Вывод строки";
        this->subblocks = {
            {"Аргумент", Subblock(this, SubblockType::INPUT, 0)},
        };
    }

    void execute(ProgramEnvironment*);
    Block* getNext();
private:
    bool isOk;
};


class LessBlock: public Block {
public:
    LessBlock(QPointF pos): Block(pos) {
        this->type = BlockType::LESS;
        this->name = "Меньше";
        this->subblocks = {
            {"Аргумент1", Subblock(this, SubblockType::INPUT, 0)},
            {"Аргумент2", Subblock(this, SubblockType::INPUT, 1)},
            {"Если", Subblock(this, SubblockType::GOTO, 2)},
            {"Иначе", Subblock(this, SubblockType::GOTO, 3)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 4)}
        };
    }
    void execute(ProgramEnvironment*);
    Block* getNext();
};

class EqualBlock: public Block {
public:
    EqualBlock(QPointF pos): Block(pos) {
        this->type = BlockType::EQUAL;
        this->name = "Равно";
        this->subblocks = {
            {"Аргумент1", Subblock(this, SubblockType::INPUT, 0)},
            {"Аргумент2", Subblock(this, SubblockType::INPUT, 1)},
            {"Если", Subblock(this, SubblockType::GOTO, 2)},
            {"Иначе", Subblock(this, SubblockType::GOTO, 3)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 4)}
        };
    }
    void execute(ProgramEnvironment*);
    Block* getNext();
};

class BiggerBlock: public Block {
public:
    BiggerBlock(QPointF pos): Block(pos) {
        this->type = BlockType::BIGGER;
        this->name = "Больше";
        this->subblocks = {
            {"Аргумент1", Subblock(this, SubblockType::INPUT, 0)},
            {"Аргумент2", Subblock(this, SubblockType::INPUT, 1)},
            {"Если", Subblock(this, SubblockType::GOTO, 2)},
            {"Иначе", Subblock(this, SubblockType::GOTO, 3)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 4)}
        };
    }
    void execute(ProgramEnvironment*);
    Block* getNext();
};

class EqualsBlock: public Block {
public:
    EqualsBlock(QPointF pos): Block(pos) {
        this->type = BlockType::EQUALS;
        this->name = "Сравнение";
        this->subblocks = {
            {"Строка 1", Subblock(this, SubblockType::INPUT, 0)},
            {"Строка 2", Subblock(this, SubblockType::INPUT, 1)},
            {"Равны", Subblock(this, SubblockType::GOTO, 2)},
            {"Не равны", Subblock(this, SubblockType::GOTO, 3)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 4)}
        };
    }
    void execute(ProgramEnvironment*);
    Block* getNext();
};

class FindBlock: public Block {
public:
    FindBlock(QPointF pos): Block(pos) {
        this->type = BlockType::FIND;
        this->name = "Поиск";
        this->subblocks = {
            {"Строка", Subblock(this, SubblockType::INPUT, 0)},
            {"Подстрока", Subblock(this, SubblockType::INPUT, 1)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 2)}
        };
    }
    void execute(ProgramEnvironment*);
};

class ReplaceBlock: public Block {
public:
    ReplaceBlock(QPointF pos): Block(pos) {
        this->type = BlockType::REPLACE;
        this->name = "Заменить";
        this->subblocks = {
            {"Строка", Subblock(this, SubblockType::INPUT, 0)},
            {"Подстрока", Subblock(this, SubblockType::INPUT, 1)},
            {"Позиция", Subblock(this, SubblockType::INPUT, 2)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 3)}
        };
    }
    void execute(ProgramEnvironment*);
};

class ReverseBlock: public Block {
public:
    ReverseBlock(QPointF pos): Block(pos) {
        this->type = BlockType::REVERSE;
        this->name = "Перевернуть";
        this->subblocks = {
            {"Строка", Subblock(this, SubblockType::INPUT, 0)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 1)}
        };
    }
    void execute(ProgramEnvironment*);
};

class NegationBlock: public Block {
public:
    NegationBlock(QPointF pos): Block(pos) {
        this->type = BlockType::NEGATION;
        this->name = "Отрицание";
        this->subblocks = {
            {"Аргумент", Subblock(this, SubblockType::INPUT, 0)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 1)}
        };

    }

    void execute(ProgramEnvironment*);
};

class ConjunctionBlock: public Block {
public:
    ConjunctionBlock(QPointF pos): Block(pos) {
        this->type = BlockType::CONJUNCTION;
        this->name = "Конъюнкция";
        this->subblocks = {
            {"Аргумент1", Subblock(this, SubblockType::INPUT, 0)},
            {"Аргумент2", Subblock(this, SubblockType::INPUT, 1)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 2)}
        };

    }

    void execute(ProgramEnvironment*);
};

class DisjunctionBlock: public Block {
public:
    DisjunctionBlock(QPointF pos): Block(pos) {
        this->type = BlockType::DISJUNCTION;
        this->name = "Дизъюнкция";
        this->subblocks = {
            {"Аргумент1", Subblock(this, SubblockType::INPUT, 0)},
            {"Аргумент2", Subblock(this, SubblockType::INPUT, 1)},
            {"Результат", Subblock(this, SubblockType::OUTPUT, 2)}
        };

    }

    void execute(ProgramEnvironment*);
};

#endif // BLOCKS_H
