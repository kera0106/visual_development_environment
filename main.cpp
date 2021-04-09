#include "mainwindow.h"

#include "blocks.h"
#include "programm.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.showMaximized();


    BeginBlock beginBlock;

    NumberInputBlock input1(&w);
    NumberInputBlock input2(&w);

    DivBlock sum;

    NumberOutputBlock output(&w);

    beginBlock.setEnd(&input1);
    input1.setEnd(&input2);
    input2.setEnd(&sum);
    sum.setEnd(&output);

    sum.getSubblock("Argument 1")->LinkTo(input1.getSubblock("Result"));
    sum.getSubblock("Argument 2")->LinkTo(input2.getSubblock("Result"));

    output.getSubblock("Argument 1")->LinkTo(sum.getSubblock("Result"));

    Programm programm(&beginBlock);
    programm.execute();

    return a.exec();
}
