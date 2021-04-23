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

void StringInputBlock::execute()
{
    this->result = QInputDialog::getText(parent, "Ввод строки", "Строка:");


    if (end) {
        end->execute();
    }
}

void StringOutputBlock::execute()
{
    QMessageBox::information(parent, "Вывод строки", getSubblock("Аргумент")->getResult().toString());

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

void ConcatBlock::execute()
{
    QString arg1 = getSubblock("Строка 1")->getResult().toString();
    QString arg2 = getSubblock("Строка 2")->getResult().toString();

    this->result = arg1 + arg2;

    if (end) {
        end->execute();
    }
}

void SubstringBlock::execute()
{
    QString str = getSubblock("Строка")->getResult().toString();
    int startStr = getSubblock("Начало")->getResult().toInt();
    int endStr = getSubblock("Конец")->getResult().toInt();

    this->result = str.mid(startStr, endStr-startStr);

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

    auto true_block = getSubblock("Если")->getLink().blockLink;
    auto false_block = getSubblock("Иначе")->getLink().blockLink;

    this->result = arg1 < arg2;

    if (result.toBool() && true_block) {
        true_block->execute();
    } else if (!result.toBool() && false_block) {
        false_block->execute();
    } else {
        end->execute();
    }
}

void BiggerBlock::execute()
{
    int arg1 = getSubblock("Аргумент1")->getResult().toInt();
    int arg2 = getSubblock("Аргумент2")->getResult().toInt();

    auto true_block = getSubblock("Если")->getLink().blockLink;
    auto false_block = getSubblock("Иначе")->getLink().blockLink;

    this->result = arg1 > arg2;

    if (result.toBool() && true_block) {
        true_block->execute();
    } else if (!result.toBool() && false_block) {
        false_block->execute();
    } else {
        end->execute();
    }

}

void EqualBlock::execute()
{
    int arg1 = getSubblock("Аргумент1")->getResult().toInt();
    int arg2 = getSubblock("Аргумент2")->getResult().toInt();

    auto true_block = getSubblock("Если")->getLink().blockLink;
    auto false_block = getSubblock("Иначе")->getLink().blockLink;

    this->result = arg1 == arg2;

    if (result.toBool() && true_block) {
        true_block->execute();
    } else if (!result.toBool() && false_block) {
        false_block->execute();
    } else {
        end->execute();
    }
}

void EqualsBlock::execute()
{
    QString arg1 = getSubblock("Строка 1")->getResult().toString();
    QString arg2 = getSubblock("Строка 2")->getResult().toString();

    auto true_block = getSubblock("Равны")->getLink().blockLink;
    auto false_block = getSubblock("Не равны")->getLink().blockLink;

    this->result = arg1 == arg2;

    if (result.toBool() && true_block) {
        true_block->execute();
    } else if (!result.toBool() && false_block) {
        false_block->execute();
    } else {
        end->execute();
    }
}

void FindBlock::execute()
{
    QString string = getSubblock("Строка")->getResult().toString();
    QString substring = getSubblock("Подстрока")->getResult().toString();

    this->result = string.indexOf(substring);

    if (end) {
        end->execute();
    }
}

void ReplaceBlock::execute()
{
    QString string = getSubblock("Строка")->getResult().toString();
    QString substring = getSubblock("Подстрока")->getResult().toString();
    int pos = getSubblock("Позиция")->getResult().toInt();

    this->result = string.replace(pos, substring.length(), substring);

    if (end) {
        end->execute();
    }
}

void ReverseBlock::execute()
{
    QString string = getSubblock("Строка")->getResult().toString();
    QString resString = "";
    for (int i=string.length()-1; i>=0; i--){
        resString += string[i];
    }

    this->result = resString;

    if (end) {
        end->execute();
    }
}
