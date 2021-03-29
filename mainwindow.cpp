#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->fileLayout->setAlignment(Qt::AlignLeft);
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
