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
    QMessageBox::information(parent, "Вывод числа", this->subblocks["Argument 1"].getResult().toString());

    if (end) {
        end->execute();
    }
}

void SumBlock::execute()
{
    int arg1 = this->subblocks["Argument 1"].getResult().toInt();
    int arg2 = this->subblocks["Argument 2"].getResult().toInt();

    this->result = arg1 + arg2;

    if (end) {
        end->execute();
    }
}

void DiffBlock::execute()
{
    int arg1 = this->subblocks["Argument 1"].getResult().toInt();
    int arg2 = this->subblocks["Argument 2"].getResult().toInt();

    this->result = arg1 - arg2;

    if (end) {
        end->execute();
    }
}

void MultBlock::execute()
{
    int arg1 = this->subblocks["Argument 1"].getResult().toInt();
    int arg2 = this->subblocks["Argument 2"].getResult().toInt();

    this->result = arg1 * arg2;

    if (end) {
        end->execute();
    }
}

void DivBlock::execute()
{
    int arg1 = this->subblocks["Argument 1"].getResult().toInt();
    int arg2 = this->subblocks["Argument 2"].getResult().toInt();

    this->result = arg1 / arg2;

    if (end) {
        end->execute();
    }
}

void ModBlock::execute()
{
    int arg1 = this->subblocks["Argument 1"].getResult().toInt();
    int arg2 = this->subblocks["Argument 2"].getResult().toInt();

    this->result = arg1 % arg2;

    if (end) {
        end->execute();
    }
}

void PowBlock::execute()
{
    int arg1 = this->subblocks["Argument 1"].getResult().toInt();
    int arg2 = this->subblocks["Argument 2"].getResult().toInt();

    this->result = pow(arg1, arg2);

    if (end) {
        end->execute();
    }
}

void SqrtBlock::execute()
{
    int arg1 = this->subblocks["Argument"].getResult().toInt();

    this->result = sqrt(arg1);

    std::cout << arg1 << std::endl;
    std::cout << this->result.toFloat() << std::endl;

    if (end) {
        end->execute();
    }
}
