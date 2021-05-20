#ifndef THREADDIALOGCONNECTOR_H
#define THREADDIALOGCONNECTOR_H

#include <QObject>
#include <QInputDialog>
#include <QMessageBox>

class ThreadDialogConnector: public QObject {
    Q_OBJECT

public slots:

    void showInputIntDialog() {
        QInputDialog dialog(nullptr);
        dialog.setWindowTitle("Ввод числа");
        dialog.setLabelText("Число:");
        dialog.setIntRange(-2147483647, 2147483647);
        dialog.setIntValue(0);
        dialog.setIntStep(1);

        int ret = dialog.exec();
        emit dialogResult(dialog.intValue(), !!ret);
    }

    void showInputTextDialog() {
        QInputDialog dialog(nullptr);
        dialog.setWindowTitle("Ввод строки");
        dialog.setLabelText("Строка:");

        int ret = dialog.exec();
        emit dialogResult(dialog.textValue(), !!ret);
    }

    void showText(QString title, QString text) {
        auto ret = QMessageBox::information(nullptr, title, text, QMessageBox::Ok, QMessageBox::Cancel);
        emit dialogResult(QVariant(), ret == QMessageBox::Ok);
    }

signals:

    void dialogResult(QVariant result, bool isOk);

};

#endif // THREADDIALOGCONNECTOR_H
