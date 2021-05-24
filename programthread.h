#ifndef PROGRAMTHREAD_H
#define PROGRAMTHREAD_H

#include "program.h"

#include <QThread>


class ProgramThread: public QThread {

public:
    ProgramThread(Program *program): program(program) {}

    // QThread interface
protected:
    void run() {
        program->execute();
    }

private:
    Program *program;
};

#endif // PROGRAMTHREAD_H
