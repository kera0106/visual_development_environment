#ifndef PROGRAMENVIRONMENT_H
#define PROGRAMENVIRONMENT_H

#include <QInputDialog>
#include <QMutex>
#include <QObject>
#include <QWaitCondition>
#include <QDebug>

class ProgramEnvironment: public QObject {

    Q_OBJECT

public:

    QVariant getInt() {
        emit showInputIntDialog();

        pause.lock();
        pauseCondition.wait(&pause);
        pause.unlock();

        return result;
    }

    QVariant getText() {
        emit showInputTextDialog();

        pause.lock();
        pauseCondition.wait(&pause);
        pause.unlock();

        return result;
    }

    void output(QString title, QString text) {
        emit showText(title, text);
        qDebug() << "Test";
    }

public slots:
    void onDialogResult(QVariant result) {
        pause.lock();
        this->result = result;
        pause.unlock();

        pauseCondition.wakeAll();
    }

signals:

    void showInputIntDialog();
    void showInputTextDialog();
    void showText(QString title, QString text);

private:

    QMutex pause;
    QWaitCondition pauseCondition;
    QVariant result;

};

#endif // PROGRAMENVIRONMENT_H
