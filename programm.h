#ifndef PROGRAMM_H
#define PROGRAMM_H

#include "block.h"

class Programm
{
public:
    Programm() {}
    Programm(Block *beginBlock): beginBlock(beginBlock) {}

    void execute() { beginBlock->execute(); }
    void setBegin(Block *beginBlock) { this->beginBlock = beginBlock; }

private:
    Block *beginBlock;
};

#endif // PROGRAMM_H
