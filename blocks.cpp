#include "blocks.h"

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
