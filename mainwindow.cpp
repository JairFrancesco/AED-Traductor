#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <string.h>
#include <fstream>
#include <iostream>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QStandardItem>
#include <palabra.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Cargar contenido al combobox
    ui->cbTiposEDs->addItem("Red-Black Tree");
    ui->cbTiposEDs->addItem("AVL Tree");
    ui->cbTiposEDs->addItem("Arbol Binario de Busqueda");

    //TableView
    this->model->setHorizontalHeaderItem(0, new QStandardItem(QString("Idioma 1")));
    this->model->setHorizontalHeaderItem(1, new QStandardItem(QString("Idioma 2")));
    ui->tblDiccionario->setModel(this->model);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//Por el momento funciona solo con Red-Black Tree
void MainWindow::cargarDatos(QString _rutaArchivo)
{
  std::string rutaArchivo = _rutaArchivo.toUtf8().constData();
  std::string line;
  RBTree<Palabra> *arbol = new RBTree<Palabra>();
  ifstream myfile (rutaArchivo);

  QTime myTimer;
  myTimer.start();
  string idioma1;
  string idioma2;

  string::size_type pos;
  int rowCount = 0;
  if (myfile.is_open())
  {
    while (getline (myfile,line))
    {
        if (line.substr(0,1)!="#") //Evitar las lineas comentadas
        {
            pos=line.find("\t", 0);
            if (pos>0) //Si es menor, entonces no hay tabs
            {
                idioma1 = line.substr(0,pos);
                idioma2 = line.substr(pos+1);

                QString item1 = QString::fromStdString(idioma1);
                QString item2 = QString::fromStdString(idioma2);
                this->model->setItem(rowCount,0, new QStandardItem(item1));
                this->model->setItem(rowCount,1, new QStandardItem(item2));
                cout<<"Idioma1:"<<idioma1<<"Idioma2:"<<idioma2<<endl;
                Palabra p(idioma1, idioma2);
                //arbol->insertar(p);
                //this->model->setRowCount(this->model->rowCount()+1);
            }
            rowCount++;
        }
    }
    myfile.close();
  }
  else QMessageBox::information(0, "error, No se pudo abrir el archivo", QString("Error"));
  int nMilliseconds = myTimer.elapsed();
  QString s = QString::number(nMilliseconds);
  ui->txtTiempoCarga->setText(s);
  ui->tblDiccionario->setModel(this->model);
}

void MainWindow::on_btnOpenFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir diccionario"), ".", tr("Archivos de texto (*.txt)"));
    if (!fileName.isEmpty())
    {
        ui->txtFilePath->setText(fileName);
        //Cargar palabras al arbol y calcular tiempo de carga
        cargarDatos(fileName);

    }
    else
    {
        QMessageBox m; m.setText("No se ha seleccionado un diccionario"); m.exec();
    }

}

/*
void MainWindow::on_pushButton_clicked()
{
    if (ui->txtFilePath->text()=="")
    {
        QMessageBox m; m.setText("No se ha seleccionado un diccionario"); m.exec();
        QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir diccionario"), ".", tr("Archivos de texto (*.txt)"));
        ui->txtFilePath->setText(fileName);
    }
}
*/

void MainWindow::on_cbTiposEDs_currentIndexChanged(int index)
{
    QMessageBox* msgBox;
    msgBox  = new QMessageBox();
    msgBox->setWindowTitle("Mensaje de prueba");
    if (index==0)
    {
        msgBox->setText("Ha Seleccionado Red-Black");
        msgBox->show();
    } else if (index==1)
    {
        msgBox->setText("Ha Seleccionado AVL");
        msgBox->show();
    } else
    {
        msgBox->setText("Ha Seleccionado otros");
        msgBox->show();
    }

}

void MainWindow::on_txtPalabra_returnPressed()
{
    QMessageBox m; m.setText("Mensaje de prueba enter"); m.exec();
}
