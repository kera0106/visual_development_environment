#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graphicscene.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_open_clicked();

    void on_run_clicked();

    void on_stop_clicked();

    void on_save_clicked();

    void slotTimer();

private:
    void resizeEvent(QResizeEvent * event);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    GraphicScene *scene;
};
#endif // MAINWINDOW_H
