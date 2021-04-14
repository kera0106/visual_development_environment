#include "blocks.h"
#include <iostream>

void BeginBlock::execute()
{
    if (end) {
        end->execute();
    }
}

void NumberInputBlock::execute()
{
    this->result = QInputDialog::getInt(parent, "Ввод числа", "Число:");


    if (end) {
        end->execute();
    }
}

void NumberOutputBlock::execute()
{
    QMessageBox::information(parent, "Вывод числа", getSubblock("Аргумент")->getResult().toString());

    if (end) {
        end->execute();
    }
}

void SumBlock::execute()
{
    int arg1 = getSubblock("Слагаемое 1")->getResult().toInt();
    int arg2 = getSubblock("Слагаемое 2")->getResult().toInt();

    this->result = arg1 + arg2;

    if (end) {
        end->execute();
    }
}

void DiffBlock::execute()
{
    int arg1 = getSubblock("Уменьшаемое")->getResult().toInt();
    int arg2 = getSubblock("Вычитаемое")->getResult().toInt();

    this->result = arg1 - arg2;

    if (end) {
        end->execute();
    }
}

void MultBlock::execute()
{
    int arg1 = getSubblock("Множитель 1")->getResult().toInt();
    int arg2 = getSubblock("Множитель 2")->getResult().toInt();

    this->result = arg1 * arg2;

    if (end) {
        end->execute();
    }
}

void DivBlock::execute()
{
    int arg1 = getSubblock("Делимое")->getResult().toInt();
    int arg2 = getSubblock("Делитель")->getResult().toInt();

    this->result = arg1 / arg2;

    if (end) {
        end->execute();
    }
}

void ModBlock::execute()
{
    int arg1 = getSubblock("Делимое")->getResult().toInt();
    int arg2 = getSubblock("Делитель")->getResult().toInt();

    this->result = arg1 % arg2;

    if (end) {
        end->execute();
    }
}

void PowBlock::execute()
{
    int arg1 = getSubblock("Основание")->getResult().toInt();
    int arg2 = getSubblock("Показатель")->getResult().toInt();

    this->result = pow(arg1, arg2);

    if (end) {
        end->execute();
    }
}

void SqrtBlock::execute()
{
    int arg1 = getSubblock("Аргумент")->getResult().toInt();

    this->result = sqrt(arg1);

    std::cout << arg1 << std::endl;
    std::cout << this->result.toFloat() << std::endl;

    if (end) {
        end->execute();
    }
}

void LessBlock::execute()
{
    int arg1 = getSubblock("Аргумент1")->getResult().toInt();
    int arg2 = getSubblock("Аргумент2")->getResult().toInt();

    this->result = arg1 < arg2? arg1: arg2;

    if (end) {
        end->execute();
    }
}

void BiggerBlock::execute()
{
    int arg1 = getSubblock("Аргумент1")->getResult().toInt();
    int arg2 = getSubblock("Аргумент2")->getResult().toInt();

    this->result = arg1 > arg2? arg1: arg2;

    if (end) {
        end->execute();
    }
}

void EqualBlock::execute()
{
    int arg1 = getSubblock("Аргумент1")->getResult().toInt();
    int arg2 = getSubblock("Аргумент2")->getResult().toInt();

    this->result = arg1 == arg2;

    if (end) {
        end->execute();
    }
}
