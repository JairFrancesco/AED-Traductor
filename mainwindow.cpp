#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnOpenFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir diccionario"), ".", tr("Archivos de texto (*.txt)"));
    if (!fileName.isEmpty())
    {
        ui->lineEdit_2->setText(fileName);
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->lineEdit_2->text()=="")
    {
        QMessageBox m; m.setText("No se a seleccionado un diccionario"); m.exec();
        QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir diccionario"), ".", tr("Archivos de texto (*.txt)"));
        ui->lineEdit_2->setText(fileName);
    }
}
