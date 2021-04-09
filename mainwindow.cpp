#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->fileLayout->setAlignment(Qt::AlignLeft);

    scene = new GraphicScene(this);
        ui->canvas->setScene(scene);

        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
        timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_open_clicked()
{
    QMessageBox::about(this, "Нажатие кнопки", "Кнопка открыть");
}

void MainWindow::on_run_clicked()
{
    QMessageBox::about(this, "Нажатие кнопки", "Кнопка запуск");
}

void MainWindow::on_stop_clicked()
{
    QMessageBox::about(this, "Нажатие кнопки", "Кнопка стоп");
}

void MainWindow::on_save_clicked()
{
    QMessageBox::about(this, "Нажатие кнопки", "Кнопка сохранить");
}

void MainWindow::slotTimer()
{
    timer->stop();
    scene->setSceneRect(0,0, ui->canvas->width() - 20, ui->canvas->height() - 20);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}

void MainWindow::on_start_clicked()
{
    scene->setButtonType(START);
}

void MainWindow::on_input_clicked()
{
    scene->setButtonType(INPUT);
}

void MainWindow::on_sum_clicked()
{
    scene->setButtonType(SUM);
}

void MainWindow::on_output_clicked()
{
    scene->setButtonType(OUTPUT);
}

void MainWindow::on_diff_clicked()
{
    scene->setButtonType(DIFF);
}

void MainWindow::on_mult_clicked()
{
    scene->setButtonType(MULT);
}

void MainWindow::on_divide_clicked()
{
    scene->setButtonType(DIVIDE);
}

void MainWindow::on_mod_clicked()
{
    scene->setButtonType(MOD);
}

void MainWindow::on_pow_clicked()
{
    scene->setButtonType(POW);
}

void MainWindow::on_sqrt_clicked()
{
    scene->setButtonType(SQRT);
}
