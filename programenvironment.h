#ifndef PROGRAMENVIRONMENT_H
#define PROGRAMENVIRONMENT_H

#include <QObject>

class ProgramEnvironment: public QObject {

    Q_OBJECT

public:

    void printHello() {
        emit showDialog();
    }

signals:

    void showDialog();

};

#endif // PROGRAMENVIRONMENT_H
