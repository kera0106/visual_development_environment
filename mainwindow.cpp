#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>

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

void MainWindow::on_run_clicked()
{
    programEnvironment = new ProgramEnvironment();
    QObject::connect(programEnvironment, &ProgramEnvironment::showInputIntDialog,  &this->TDConnector, &ThreadDialogConnector::showInputIntDialog);
    QObject::connect(programEnvironment, &ProgramEnvironment::showInputTextDialog, &this->TDConnector, &ThreadDialogConnector::showInputTextDialog);
    QObject::connect(programEnvironment, &ProgramEnvironment::showText,            &this->TDConnector, &ThreadDialogConnector::showText);

    QObject::connect(&this->TDConnector, &ThreadDialogConnector::dialogResult, programEnvironment, &ProgramEnvironment::onDialogResult);

    auto &program = scene->getProgram();
    program.setEnvironment(programEnvironment);

    programThread = new ProgramThread(&program);
    QObject::connect(programThread, &ProgramThread::finished, this, &MainWindow::on_program_finished);

    programThread->start();

    ui->run->setEnabled(false);
    ui->stop->setEnabled(true);
}

void MainWindow::on_stop_clicked()
{
    auto &program = scene->getProgram();
    program.stop();
}

void MainWindow::on_open_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this, tr("Open program"), QString(), "Program (*.vbpl)");
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file.");
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(file.readAll());

    Program p(document.object());
    scene->setProgram(p);
}

void MainWindow::on_save_clicked()
{   
    QJsonObject json = scene->getProgram().toJSON();

    QFileDialog dialog(this, "Save program", QString(),
                       "Program (*.vbpl)");
    dialog.setDefaultSuffix(".vbpl");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec()) {
        const auto fileName = dialog.selectedFiles().front();

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            qWarning("Couldn't open file.");
            return;
        }

        file.write(QJsonDocument(json).toJson());
    }
}

void MainWindow::on_program_finished()
{
    ui->run->setEnabled(true);
    ui->stop->setEnabled(false);

    delete programThread;
    delete programEnvironment;

    programThread = nullptr;
    programEnvironment = nullptr;
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

void MainWindow::on_less_clicked()
{
    scene->setButtonType(LESS);
}

void MainWindow::on_bigger_clicked()
{
    scene->setButtonType(BIGGER);
}

void MainWindow::on_equal_clicked()
{
    scene->setButtonType(EQUAL);
}

void MainWindow::on_inputString_clicked()
{
    scene->setButtonType(INPUT_STR);
}

void MainWindow::on_outputString_clicked()
{
    scene->setButtonType(OUTPUT_STR);
}

void MainWindow::on_concat_clicked()
{
    scene->setButtonType(CONCAT);
}

void MainWindow::on_substring_clicked()
{
    scene->setButtonType(SUBSTRING);
}

void MainWindow::on_equals_clicked()
{
    scene->setButtonType(EQUALS);
}

void MainWindow::on_find_clicked()
{
    scene->setButtonType(FIND);
}

void MainWindow::on_replace_clicked()
{
    scene->setButtonType(REPLACE);
}

void MainWindow::on_reverse_clicked()
{
    scene->setButtonType(REVERSE);
}

void MainWindow::on_negation_clicked()
{
    scene->setButtonType(NEGATION);
}

void MainWindow::on_conjunction_clicked()
{
    scene->setButtonType(CONJUNCTION);
}

void MainWindow::on_disjunction_clicked()
{
    scene->setButtonType(DISJUNCTION);
}

void MainWindow::on_clear_clicked()
{
    scene->clearCanvas();
}
