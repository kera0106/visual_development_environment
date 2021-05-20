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

    QVariant getInt(bool *isOk) {
        emit showInputIntDialog();

        pause.lock();
        pauseCondition.wait(&pause);
        pause.unlock();

        if (isOk) {
            *isOk = this->isOk;
        }

        return result;
    }

    QVariant getText(bool *isOk) {
        emit showInputTextDialog();

        pause.lock();
        pauseCondition.wait(&pause);
        pause.unlock();

        if (isOk) {
            *isOk = this->isOk;
        }

        return result;
    }

    bool output(QString title, QString text) {
        emit showText(title, text);

        pause.lock();
        pauseCondition.wait(&pause);
        pause.unlock();

        return isOk;
    }

public slots:
    void onDialogResult(QVariant result, bool isOk) {
        pause.lock();
        this->result = result;
        this->isOk = isOk;
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
    bool isOk;

};

#endif // PROGRAMENVIRONMENT_H
