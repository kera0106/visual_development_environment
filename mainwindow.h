#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graphicscene.h"
#include "programthread.h"
#include "threaddialogconnector.h"

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

    void on_program_finished();

    void slotTimer();

    void on_start_clicked();

    void on_input_clicked();

    void on_sum_clicked();

    void on_output_clicked();

    void on_diff_clicked();

    void on_mult_clicked();

    void on_divide_clicked();

    void on_mod_clicked();

    void on_pow_clicked();

    void on_sqrt_clicked();

    void on_less_clicked();

    void on_bigger_clicked();

    void on_equal_clicked();

    void on_inputString_clicked();

    void on_outputString_clicked();

    void on_concat_clicked();

    void on_substring_clicked();

    void on_equals_clicked();

    void on_find_clicked();

    void on_replace_clicked();

    void on_reverse_clicked();

    void on_clear_clicked();

    void on_negation_clicked();

    void on_disjunction_clicked();

    void on_conjunction_clicked();

private:
    void resizeEvent(QResizeEvent * event);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    GraphicScene *scene;

    ProgramThread *programThread = nullptr;
    ProgramEnvironment *programEnvironment = nullptr;
    ThreadDialogConnector TDConnector;
};
#endif // MAINWINDOW_H
