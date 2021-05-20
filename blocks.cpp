#include "blocks.h"
#include <iostream>

int Block::current_id = 0;

void BeginBlock::execute(ProgramEnvironment* env)
{
    env->printHello();
}

void NumberInputBlock::execute(ProgramEnvironment* env)
{
    this->result = QInputDialog::getInt(parent, "Ввод числа", "Число:");
}

void NumberOutputBlock::execute(ProgramEnvironment* env)
{
    QMessageBox::information(parent, "Вывод числа", getSubblock("Аргумент")->getResult().toString());
}

void StringInputBlock::execute(ProgramEnvironment* env)
{
    this->result = QInputDialog::getText(parent, "Ввод строки", "Строка:");
}

void StringOutputBlock::execute(ProgramEnvironment* env)
{
    QMessageBox::information(parent, "Вывод строки", getSubblock("Аргумент")->getResult().toString());
}

void SumBlock::execute(ProgramEnvironment* env)
{
    int arg1 = getSubblock("Слагаемое 1")->getResult().toInt();
    int arg2 = getSubblock("Слагаемое 2")->getResult().toInt();

    this->result = arg1 + arg2;
}

void ConcatBlock::execute(ProgramEnvironment* env)
{
    QString arg1 = getSubblock("Строка 1")->getResult().toString();
    QString arg2 = getSubblock("Строка 2")->getResult().toString();

    this->result = arg1 + arg2;
}

void SubstringBlock::execute(ProgramEnvironment* env)
{
    QString str = getSubblock("Строка")->getResult().toString();
    int startStr = getSubblock("Начало")->getResult().toInt();
    int endStr = getSubblock("Конец")->getResult().toInt();

    this->result = str.mid(startStr, endStr-startStr);
}

void DiffBlock::execute(ProgramEnvironment* env)
{
    int arg1 = getSubblock("Уменьшаемое")->getResult().toInt();
    int arg2 = getSubblock("Вычитаемое")->getResult().toInt();

    this->result = arg1 - arg2;
}

void MultBlock::execute(ProgramEnvironment* env)
{
    int arg1 = getSubblock("Множитель 1")->getResult().toInt();
    int arg2 = getSubblock("Множитель 2")->getResult().toInt();

    this->result = arg1 * arg2;
}

void DivBlock::execute(ProgramEnvironment* env)
{
    int arg1 = getSubblock("Делимое")->getResult().toInt();
    int arg2 = getSubblock("Делитель")->getResult().toInt();

    this->result = arg1 / arg2;
}

void ModBlock::execute(ProgramEnvironment* env)
{
    int arg1 = getSubblock("Делимое")->getResult().toInt();
    int arg2 = getSubblock("Делитель")->getResult().toInt();

    this->result = arg1 % arg2;
}

void PowBlock::execute(ProgramEnvironment* env)
{
    int arg1 = getSubblock("Основание")->getResult().toInt();
    int arg2 = getSubblock("Показатель")->getResult().toInt();

    this->result = pow(arg1, arg2);
}

void SqrtBlock::execute(ProgramEnvironment* env)
{
    int arg1 = getSubblock("Аргумент")->getResult().toInt();

    this->result = sqrt(arg1);
}

void LessBlock::execute(ProgramEnvironment* env)
{
    int arg1 = getSubblock("Аргумент1")->getResult().toInt();
    int arg2 = getSubblock("Аргумент2")->getResult().toInt();

    this->result = arg1 < arg2;
}

Block *LessBlock::getNext()
{
    auto true_block = getSubblock("Если")->getLink().blockLink;
    auto false_block = getSubblock("Иначе")->getLink().blockLink;

    if (result.toBool() && true_block) {
        return true_block;
    } else if (!result.toBool() && false_block) {
        return false_block;
    } else {
        return end.getBlock();
    }
}

void BiggerBlock::execute(ProgramEnvironment* env)
{
    int arg1 = getSubblock("Аргумент1")->getResult().toInt();
    int arg2 = getSubblock("Аргумент2")->getResult().toInt();

    this->result = arg1 > arg2;
}

Block *BiggerBlock::getNext()
{

    auto true_block = getSubblock("Если")->getLink().blockLink;
    auto false_block = getSubblock("Иначе")->getLink().blockLink;

    if (result.toBool() && true_block) {
        return true_block;
    } else if (!result.toBool() && false_block) {
        return false_block;
    } else {
        return end.getBlock();
    }

}

void EqualBlock::execute(ProgramEnvironment* env)
{
    int arg1 = getSubblock("Аргумент1")->getResult().toInt();
    int arg2 = getSubblock("Аргумент2")->getResult().toInt();

    this->result = arg1 == arg2;
}

Block *EqualBlock::getNext()
{
    auto true_block = getSubblock("Если")->getLink().blockLink;
    auto false_block = getSubblock("Иначе")->getLink().blockLink;

    if (result.toBool() && true_block) {
        return true_block;
    } else if (!result.toBool() && false_block) {
        return false_block;
    } else {
        return end.getBlock();
    }

}

void EqualsBlock::execute(ProgramEnvironment* env)
{
    QString arg1 = getSubblock("Строка 1")->getResult().toString();
    QString arg2 = getSubblock("Строка 2")->getResult().toString();

    this->result = arg1 == arg2;
}

Block *EqualsBlock::getNext()
{

    auto true_block = getSubblock("Равны")->getLink().blockLink;
    auto false_block = getSubblock("Не равны")->getLink().blockLink;

    if (result.toBool() && true_block) {
        return true_block;
    } else if (!result.toBool() && false_block) {
        return false_block;
    } else {
        return end.getBlock();
    }

}

void FindBlock::execute(ProgramEnvironment* env)
{
    QString string = getSubblock("Строка")->getResult().toString();
    QString substring = getSubblock("Подстрока")->getResult().toString();

    this->result = string.indexOf(substring);
}

void ReplaceBlock::execute(ProgramEnvironment* env)
{
    QString string = getSubblock("Строка")->getResult().toString();
    QString substring = getSubblock("Подстрока")->getResult().toString();
    int pos = getSubblock("Позиция")->getResult().toInt();

    this->result = string.replace(pos, substring.length(), substring);
}

void ReverseBlock::execute(ProgramEnvironment* env)
{
    QString string = getSubblock("Строка")->getResult().toString();
    QString resString = "";
    for (int i=string.length()-1; i>=0; i--){
        resString += string[i];
    }

    this->result = resString;
}

void NegationBlock::execute(ProgramEnvironment* env)
{
    bool arg = getSubblock("Аргумент")->getResult().toBool();

    this->result = int(!arg);
}

void ConjunctionBlock::execute(ProgramEnvironment* env)
{
    bool arg1 = getSubblock("Аргумент1")->getResult().toBool();
    bool arg2 = getSubblock("Аргумент2")->getResult().toBool();

    this->result = int(arg1 && arg2);
}

void DisjunctionBlock::execute(ProgramEnvironment* env)
{
    bool arg1 = getSubblock("Аргумент1")->getResult().toBool();
    bool arg2 = getSubblock("Аргумент2")->getResult().toBool();

    this->result = int(arg1 || arg2);
}
